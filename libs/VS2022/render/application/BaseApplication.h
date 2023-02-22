#pragma once

#include "BaseEngine.h"

#include <memory>

namespace ll
{

class BaseApplication 
{
public:
    virtual ~BaseApplication() = default;
    virtual int32_t Init() = 0;
    virtual int32_t Run(int argc, char* argv[]) = 0;
    virtual void Pause() = 0;
    virtual void Resume() = 0;
    virtual void Restart() = 0;
    virtual void Close() = 0;
    virtual BaseEngine::Ptr GetEngine() const = 0;
};

}