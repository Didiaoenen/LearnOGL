#include "Engine.h"

#include "ProgramLib.h"
#include "DeviceManager.h"
#include "BuiltinResManager.h"

ll::Engine::Engine()
{
}

ll::Engine::~Engine()
{
}

int32_t ll::Engine::Init()
{
    _gfxDevice = ll::DeviceManager::Create();
    _programLib = new ProgramLib();
    _builtinResManager = new BuiltinResManager;

    _inited = true;

    return 0;
}

int32_t ll::Engine::Run()
{
    BasePlatform* platform = BasePlatform::GetPlatform();
    platform->RunInPlatformThread([&]() { Tick(); });
    return 0;
}

void ll::Engine::Pause()
{
}

void ll::Engine::Resume()
{
}

int ll::Engine::Restart()
{
    return 0;
}

void ll::Engine::Close()
{
}

void ll::Engine::SetPreferredFramesPerSecond(int fps)
{
}

ll::uint ll::Engine::GetTotalFrames() const
{
    return _totalFrames;
}

void ll::Engine::Destroy()
{
}

void ll::Engine::Tick()
{
    if (_needRestart) {
        DoRestart();
        _needRestart = false;
    }

    static std::chrono::steady_clock::time_point prevTime;
    static std::chrono::steady_clock::time_point now;
    static float dt = 0.F;
    static double dtNS = NANOSECONDS_60FPS;

    ++_totalFrames;

    if (dtNS < static_cast<double>(_prefererredNanosecondsPerFrame)) 
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds(_prefererredNanosecondsPerFrame - static_cast<int64_t>(dtNS)));
        dtNS = static_cast<double>(_prefererredNanosecondsPerFrame);
    }

    prevTime = std::chrono::steady_clock::now();
    now = std::chrono::steady_clock::now();
    dtNS = dtNS * 0.1 + 0.9 * static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(now - prevTime).count());
    dt = static_cast<float>(dtNS) / NANOSECONDS_PER_SECOND;
}

void ll::Engine::DoRestart()
{
}
