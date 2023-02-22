#pragma once

#include "../base/InputAssembler.h"

namespace ll
{

    class CmdDraw;
    struct GPUInputAssembler;

class glInputAssembler final : public InputAssembler
{
public:
    glInputAssembler();
    ~glInputAssembler() override;

    inline GPUInputAssembler* GpuInputAssembler() const { return _gpuInputAssembler; }

protected:
    void DoInit(const InputAssemblerInfo& info) override;
    void DoDestroy() override;

    GPUInputAssembler* _gpuInputAssembler = nullptr;
};

}