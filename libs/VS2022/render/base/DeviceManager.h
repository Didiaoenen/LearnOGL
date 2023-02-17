#pragma once

#include "Define.h"
#include "glDevice.h"

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
        DeviceInfo deviceInfo{ ll::bindingMappingInfo };
        return DeviceManager::create(deviceInfo);
    }

    static Device* create(const DeviceInfo& info) 
    {
        if (Device::instance) return Device::instance;

        Device* device = nullptr;

        if (tryCreate<glDevice>(info, &device)) return device;

        return nullptr;
    }

    static bool IsDetachDeviceThread() 
    {
        return DETACH_DEVICE_THREAD && Device::isSupportDetachDeviceThread;
    }

    static std::string getGFXName() 
    {
        std::string gfx = "gl";
        return gfx;
    }

private:
    static void AddSurfaceEventListener()
    {
        Device* device = Device::instance;
        EventDispatcher::addCustomEventListener(EVENT_DESTROY_WINDOW, [device](const CustomEvent& e) -> void {
            device->destroySurface(e.args->ptrVal);
            });

        EventDispatcher::addCustomEventListener(EVENT_RECREATE_WINDOW, [device](const CustomEvent& e) -> void {
            device->createSurface(e.args->ptrVal);
            });
    }

    template <typename DeviceCtor, typename Enable = std::enable_if_t<std::is_base_of<Device, DeviceCtor>::value>>
    static bool tryCreate(const DeviceInfo& info, Device** pDevice) 
    {
        Device* device = new DeviceCtor;

        if (IsDetachDeviceThread())
        {
            device = ccnew DeviceAgent(device);
        }

        if (!device->Initialize(info)) 
        {
            CC_SAFE_DELETE(device);
            return false;
        }

        AddSurfaceEventListener();
        *pDevice = device;

        return true;
    }

};

}