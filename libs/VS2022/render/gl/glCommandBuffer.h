#pragma once

#include "CommandBuffer.h"

#include <queue>

namespace ll
{

    struct CmdPackage;
    struct GPUPipelineState;
    struct GPUDescriptorSet;
    struct GPUInputAssembler;
    class GPUCommandAllocator;

class glCommandBuffer : public CommandBuffer
{
public:
    glCommandBuffer();
    ~glCommandBuffer() override;

    friend class Queue;

    void Begin(RenderPass* renderPass, uint32_t subpass, FrameBuffer* frameBuffer) override;
    void End() override;
    void BeginRenderPass(RenderPass* renderPass, FrameBuffer* fbo, const Rect& renderArea, const Color* colors, float depth, uint32_t stencil, CommandBuffer* const* secondaryCBs, uint32_t secondaryCBCount) override;
    void EndRenderPass() override;
    void BindPipelineState(PipelineState* pso) override;
    void BindDescriptorSet(uint32_t set, DescriptorSet* descriptorSet, uint32_t dynamicOffsetCount, const uint32_t* dynamicOffsets) override;
    void BindInputAssembler(InputAssembler* ia) override;
    void SetViewport(const Viewport& vp) override;
    void SetScissor(const Rect& rect) override;
    void SetLineWidth(float width) override;
    void SetDepthBias(float constant, float clamp, float slope) override;
    void SetBlendConstants(const Color& constants) override;
    void SetDepthBound(float minBounds, float maxBounds) override;
    void SetStencilWriteMask(StencilFace face, uint32_t mask) override;
    void SetStencilCompareMask(StencilFace face, uint32_t ref, uint32_t mask) override;
    void NextSubpass() override;
    void Draw(const DrawInfo& info) override;
    void UpdateBuffer(Buffer* buff, const void* data, uint32_t size) override;
    void CopyBuffersToTexture(const uint8_t* const* buffers, Texture* texture, const BufferTextureCopy* regions, uint32_t count) override;
    void BlitTexture(Texture* srcTexture, Texture* dstTexture, const TextureBlit* regions, uint32_t count, Filter filter) override;
    void Execute(CommandBuffer* const* cmdBuffs, uint32_t count) override;
    void Dispatch(const DispatchInfo& info) override {}
    void PipelineBarrier(const GeneralBarrier* barrier, const BufferBarrier* const* bufferBarriers, const Buffer* const* buffers, uint32_t bufferCount, const TextureBarrier* const* textureBarriers, const Texture* const* textures, uint32_t textureBarrierCount) override {}
    void BeginQuery(QueryPool* queryPool, uint32_t id) override {}
    void EndQuery(QueryPool* queryPool, uint32_t id) override {}
    void ResetQueryPool(QueryPool* queryPool) override {}

protected:
    void DoInit(const CommandBufferInfo& info) override;
    void DoDestroy() override;

    virtual void BindStates();

    GPUCommandAllocator* _cmdAllocator = nullptr;
    CmdPackage* _curCmdPackage = nullptr;
    std::queue<CmdPackage*> _pendingPackages, _freePackages;

    uint32_t _curSubpassIdx = 0U;
    GPUPipelineState* _curGPUPipelineState = nullptr;
    std::vector<GPUDescriptorSet*> _curGPUDescriptorSets;
    std::vector<std::vector<uint32_t>> _curDynamicOffsets;
    GPUInputAssembler* _curGPUInputAssember = nullptr;
    DynamicStates _curDynamicStates;

    bool _isStateInvalid = false;
};

}