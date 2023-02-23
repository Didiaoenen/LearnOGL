#include "Director.h"

#include "../core/Root.h"

#include "Device.h"

ll::Director::Director()
{
}

ll::Director::~Director()
{
}

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
    _root = new ll::Root(ll::Device::GetInstance());
    _root->Initialize({});
}
