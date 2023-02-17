#include "Device.h"

ll::Device* ll::Device::GetInstance()
{
    return nullptr;
}

ll::Device::~Device()
{
}

bool ll::Device::Initialize(const DeviceInfo& info)
{
    return false;
}

void ll::Device::Destroy()
{
}
