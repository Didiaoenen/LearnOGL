#include "glFrameBuffer.h"

#include "glDevice.h"
#include "glTexture.h"
#include "glCommands.h"
#include "glRenderPass.h"

ll::glFrameBuffer::glFrameBuffer()
{
}

ll::glFrameBuffer::~glFrameBuffer()
{
}

void ll::glFrameBuffer::DoInit(const FramebufferInfo& info)
{
    _gpuFBO = new GPUFramebuffer;
    _gpuFBO->gpuRenderPass = static_cast<glRenderPass*>(_renderPass)->GpuRenderPass();

    _gpuFBO->gpuColorTextures.resize(_colorTextures.size());
    for (size_t i = 0; i < _colorTextures.size(); ++i) {
        auto* colorTexture = static_cast<glTexture*>(_colorTextures.at(i));
        _gpuFBO->gpuColorTextures[i] = colorTexture->GpuTexture();
        _gpuFBO->lodLevel = colorTexture->GetViewInfo().baseLevel;
        ll::glDevice::GetInstance()->FramebufferHub()->Connect(colorTexture->GpuTexture(), _gpuFBO);
    }

    if (_depthStencilTexture) {
        auto* depthTexture = static_cast<glTexture*>(_depthStencilTexture);
        _gpuFBO->gpuDepthStencilTexture = depthTexture->GpuTexture();
        _gpuFBO->lodLevel = depthTexture->GetViewInfo().baseLevel;
        ll::glDevice::GetInstance()->FramebufferHub()->Connect(depthTexture->GpuTexture(), _gpuFBO);
    }

    cmdFuncCreateFramebuffer(ll::glDevice::GetInstance(), _gpuFBO);
}

void ll::glFrameBuffer::DoDestroy()
{
}
