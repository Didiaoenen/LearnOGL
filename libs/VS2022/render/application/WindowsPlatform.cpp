#include "WindowsPlatform.h"
#include "SystemWindow.h"

#include <Windows.h>

ll::WindowsPlatform::WindowsPlatform()
{
}

ll::WindowsPlatform::~WindowsPlatform()
{
}

int32_t ll::WindowsPlatform::Init()
{
    return 0;
}

int32_t ll::WindowsPlatform::Loop()
{
    UINT TARGET_RESOLUTION = 1;
    TIMECAPS tc;
    UINT wTimerRes = 0;

    if (TIMERR_NOERROR == timeGetDevCaps(&tc, sizeof(TIMECAPS))) 
    {
        wTimerRes = std::min(std::max(tc.wPeriodMin, TARGET_RESOLUTION), tc.wPeriodMax);
        timeBeginPeriod(wTimerRes);
    }

    float dt = 0.f;
    const DWORD _16ms = 16;

    LARGE_INTEGER nFreq;
    LARGE_INTEGER nLast;
    LARGE_INTEGER nNow;

    LONGLONG actualInterval = 0LL;
    LONGLONG desiredInterval = 0LL;
    LONG waitMS = 0L;

    QueryPerformanceCounter(&nLast);
    QueryPerformanceFrequency(&nFreq);

    OnResume();
    while (!_quit) 
    {
        desiredInterval = (LONGLONG)(1.0 / GetFps() * nFreq.QuadPart);
        _window->PollEvent(&_quit);
        QueryPerformanceCounter(&nNow);
        actualInterval = nNow.QuadPart - nLast.QuadPart;
        if (actualInterval >= desiredInterval) 
        {
            nLast.QuadPart = nNow.QuadPart;
            RunTask();
            _window->SwapWindow();
        }
        else 
        {
            waitMS = static_cast<LONG>((desiredInterval - actualInterval) * 1000LL / nFreq.QuadPart - 1L);
            if (waitMS > 1L)
                Sleep(waitMS);
        }
    }

    if (wTimerRes != 0)
        timeEndPeriod(wTimerRes);

    OnDestroy();

    return 0;
}