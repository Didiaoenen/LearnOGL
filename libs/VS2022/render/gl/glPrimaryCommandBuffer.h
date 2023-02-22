#pragma once

#include "glCommandBuffer.h"

#include <string>

namespace ll
{

class glPrimaryCommandBuffer final : public glCommandBuffer
{
public:
    glPrimaryCommandBuffer() = default;
    ~glPrimaryCommandBuffer() override;

    void Begin(RenderPass* renderPass, uint32_t subpass, FrameBuffer* frameBuffer) override;
    void End() override;
    void BeginRenderPass(RenderPass* renderPass, FrameBuffer* fbo, const Rect& renderArea, const Color* colors, float depth, uint32_t stencil, CommandBuffer* const* secondaryCBs, uint32_t secondaryCBCount) override;
    void EndRenderPass() override;
    void NextSubpass() override;
    void Draw(const DrawInfo& info) override;
    void SetViewport(const Viewport& vp) override;
    void SetScissor(const Rect& rect) override;
    void UpdateBuffer(Buffer* buff, const void* data, uint32_t size) override;
    void CopyBuffersToTexture(const uint8_t* const* buffers, Texture* texture, const BufferTextureCopy* regions, uint32_t count) override;
    void BlitTexture(Texture* srcTexture, Texture* dstTexture, const TextureBlit* regions, uint32_t count, Filter filter) override;
    void Execute(CommandBuffer* const* cmdBuffs, uint32_t count) override;

protected:
    friend class Queue;

    void BindStates() override;
};

}