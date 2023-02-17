#pragma once

#include "PipelineState.h"

namespace ll
{
    struct GPUPipelineState;

class glPipelineState final : public PipelineState
{
public:
    glPipelineState();
    ~glPipelineState() override;

    inline GPUPipelineState* GpuPipelineState() const { return _gpuPipelineState; }

protected:
    void DoInit(const PipelineStateInfo& info) override;
    void DoDestroy() override;

    GPUPipelineState* _gpuPipelineState = nullptr;
};

}