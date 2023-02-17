#pragma once

#include "Device.h"

namespace ll
{

class glDevice final : public Device
{
public:
    static glDevice* GetInstance();

    ~glDevice() override;

    inline GPUContext* context() const { return _gpuContext; }

protected:
    static Device* instance;

    GPUContext* _gpuContext{ nullptr };
};

}

