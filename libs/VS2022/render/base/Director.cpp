#include "Director.h"

#include "Root.h"
#include "Device.h"

double ll::Director::GetDeltaTime()
{
    return 0.0;
}

double ll::Director::GetTotalTime()
{
    return 0.0;
}

double ll::Director::GetCurrentTime()
{
    return 0.0;
}

uint32_t ll::Director::GetToaltFrames()
{
    return 0;
}

void ll::Director::GetSystem()
{
}

void ll::Director::Tick(double dt)
{
}

void ll::Director::Init()
{
    _totalFrames = 0;
    //_root = new ll::Root(Device::GetInstance());
    //_root->Initialize({});
}
