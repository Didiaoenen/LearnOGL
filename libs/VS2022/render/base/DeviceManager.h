#pragma once

#include "../gl/glDevice.h"
#include "../pipeline/Define.h"
#include "../agent/DeviceAgent.h"

namespace ll 
{

class DeviceManager final
{
    static constexpr bool DETACH_DEVICE_THREAD{ true };
    static constexpr bool FORCE_DISABLE_VALIDATION{ false };
    static constexpr bool FORCE_ENABLE_VALIDATION{ false };

public:
    static Device* Create() 
    {
        DeviceInfo deviceInfo{ bindingMappingInfo };
        return DeviceManager::Create(deviceInfo);
    }

    static Device* Create(const DeviceInfo& info) 
    {
        if (Device::instance) return Device::instance;

        Device* device = nullptr;

        if (TryCreate<glDevice>(info, &device)) return device;

        return nullptr;
    }

    static bool IsDetachDeviceThread() 
    {
        return DETACH_DEVICE_THREAD && Device::isSupportDetachDeviceThread;
    }

    static std::string GetGFXName() 
    {
        std::string gfx = "gl";
        return gfx;
    }

private:

    template <typename DeviceCtor, typename Enable = std::enable_if_t<std::is_base_of<Device, DeviceCtor>::value>>
    static bool TryCreate(const DeviceInfo& info, Device** pDevice) 
    {
        Device* device = new DeviceCtor;

        if (IsDetachDeviceThread())
        {
            device = new DeviceAgent(device);
        }

        if (!device->Initialize(info)) 
        {
            return false;
        }

        *pDevice = device;

        return true;
    }

};

}