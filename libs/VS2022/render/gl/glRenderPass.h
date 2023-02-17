#pragma once

#include "Def_common.h"
#include "glDevice.h"
#include "glObjects.h"
#include "RenderPass.h"
#include "glCommands.h"

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