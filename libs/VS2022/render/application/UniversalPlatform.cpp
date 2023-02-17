#include "UniversalPlatform.h"

extern int cocos_main(int argc, const char** argv);

int32_t ll::UniversalPlatform::Run(int argc, const char** argv)
{
    if (cocos_main(argc, argv) != 0)
    {
        return -1;
    }
    return Loop();
}

ll::ISystem::OSType ll::UniversalPlatform::GetOSType() const
{
    return GetInterface<ISystem>()->GetOSType();
}

void ll::UniversalPlatform::PollEvent()
{
}

void ll::UniversalPlatform::RunInPlatformThread(const ThreadCallback& task)
{
    _mainTask = task;
}

int32_t ll::UniversalPlatform::GetFps() const
{
    return _fps;
}

void ll::UniversalPlatform::SetFps(int32_t fps)
{
    _fps = fps;
}

void ll::UniversalPlatform::RunTask()
{
    if (_mainTask) 
    {
        _mainTask();
    }
}

void ll::UniversalPlatform::OnPause()
{
}

void ll::UniversalPlatform::OnResume()
{
}

void ll::UniversalPlatform::OnClose()
{
}

void ll::UniversalPlatform::OnDestroy()
{
}
