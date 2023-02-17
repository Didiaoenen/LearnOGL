#pragma once

#include "BasePlatform.h"

#include <memory>
#include <functional>

namespace ll
{

class BaseEngine
{
public:

    enum EngineStatus
    {
        ON_START,
        ON_PAUSE,
        ON_RESUME,
        ON_CLOSE,
        UNKNOWN,
    };
    virtual ~BaseEngine();

    using Ptr = std::shared_ptr<BaseEngine>;
    static BaseEngine::Ptr CreateEngine();

    template <class T>
    T* GetInterface() const 
    {
        BasePlatform* platform = BasePlatform::GetPlatform();
        return platform->GetInterface<T>();
    }

    virtual int32_t Init() = 0;
    virtual int32_t Run() = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual int Restart() = 0;
    virtual void Close() = 0;
    virtual uint32_t GetTotalFrames() const = 0;
    virtual void SetPreferredFramesPerSecond(int fps) = 0;

    virtual bool IsInited() const = 0;
};

}