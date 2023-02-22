#pragma once

#include "../base/RenderPass.h"

namespace ll
{

    struct GPURenderPass;

class glRenderPass final : public RenderPass
{
public:
    glRenderPass();
    ~glRenderPass() override;

    inline GPURenderPass* GpuRenderPass() const { return _gpuRenderPass; }

protected:
    void DoInit(const RenderPassInfo& info) override;
    void DoDestroy() override;

    GPURenderPass* _gpuRenderPass = nullptr;
};

}