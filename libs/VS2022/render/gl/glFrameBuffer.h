#pragma once

#include "glObjects.h"
#include "glTexture.h"
#include "glRenderPass.h"
#include "FrameBuffer.h"

namespace ll
{

class GPUFramebuffer;

class glFrameBuffer final : public FrameBuffer
{
public:
    glFrameBuffer();
    ~glFrameBuffer() override;

    inline GPUFramebuffer* GpuFBO() const { return _gpuFBO; }

protected:
    void DoInit(const FramebufferInfo& info) override;
    void DoDestroy() override;

    GPUFramebuffer* _gpuFBO = nullptr;
};

}