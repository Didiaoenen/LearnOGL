#pragma once

#include "Def_common.h"
#include "Buffer.h"
#include "RenderPass.h"
#include "FrameBuffer.h"
#include "BufferBarrier.h"
#include "PipelineState.h"
#include "DescriptorSet.h"
#include "InputAssembler.h"

namespace ll
{

class CommandBuffer
{
public:
	CommandBuffer();
	virtual ~CommandBuffer();

    void Initialize(const CommandBufferInfo& info);
    void Destroy();

    virtual void Begin(RenderPass* renderPass, uint32_t subpass, FrameBuffer* frameBuffer) = 0;
    virtual void End() = 0;
    virtual void BeginRenderPass(RenderPass* renderPass, FrameBuffer* fbo, const Rect& renderArea, const Color* colors, float depth, uint32_t stencil, CommandBuffer* const* secondaryCBs, uint32_t secondaryCBCount) = 0;
    virtual void EndRenderPass() = 0;
    virtual void BindPipelineState(PipelineState* pso) = 0;
    virtual void BindDescriptorSet(uint32_t set, DescriptorSet* descriptorSet, uint32_t dynamicOffsetCount, const uint32_t* dynamicOffsets) = 0;
    virtual void BindInputAssembler(InputAssembler* ia) = 0;
    virtual void SetViewport(const Viewport& vp) = 0;
    virtual void SetScissor(const Rect& rect) = 0;
    virtual void SetLineWidth(float width) = 0;
    virtual void SetDepthBias(float constant, float clamp, float slope) = 0;
    virtual void SetBlendConstants(const Color& constants) = 0;
    virtual void SetDepthBound(float minBounds, float maxBounds) = 0;
    virtual void SetStencilWriteMask(StencilFace face, uint32_t mask) = 0;
    virtual void SetStencilCompareMask(StencilFace face, uint32_t ref, uint32_t mask) = 0;
    virtual void NextSubpass() = 0;
    virtual void Draw(const DrawInfo& info) = 0;
    virtual void UpdateBuffer(Buffer* buff, const void* data, uint32_t size) = 0;
    virtual void CopyBuffersToTexture(const uint8_t* const* buffers, Texture* texture, const BufferTextureCopy* regions, uint32_t count) = 0;
    virtual void BlitTexture(Texture* srcTexture, Texture* dstTexture, const TextureBlit* regions, uint32_t count, Filter filter) = 0;
    virtual void Execute(CommandBuffer* const* cmdBuffs, uint32_t count) = 0;
    virtual void Dispatch(const DispatchInfo& info) = 0;
    virtual void BeginQuery(QueryPool* queryPool, uint32_t id) = 0;
    virtual void EndQuery(QueryPool* queryPool, uint32_t id) = 0;
    virtual void ResetQueryPool(QueryPool* queryPool) = 0;
    virtual void CompleteQueryPool(QueryPool* queryPool) {}

    virtual void PipelineBarrier(const GeneralBarrier* barrier, const BufferBarrier* const* bufferBarriers, const Buffer* const* buffers, uint32_t bufferBarrierCount, const TextureBarrier* const* textureBarriers, const Texture* const* textures, uint32_t textureBarrierCount) = 0;

    inline void Begin();
    inline void Begin(RenderPass* renderPass);
    inline void Begin(RenderPass* renderPass, uint32_t subpass);

    inline void UpdateBuffer(Buffer* buff, const void* data);

    inline void Execute(const CommandBufferList& cmdBuffs, uint32_t count);

    inline void BindDescriptorSet(uint32_t set, DescriptorSet* descriptorSet);
    inline void BindDescriptorSet(uint32_t set, DescriptorSet* descriptorSet, const std::vector<uint32_t>& dynamicOffsets);

    inline void BeginRenderPass(RenderPass* renderPass, FrameBuffer* fbo, const Rect& renderArea, const ColorList& colors, float depth, uint32_t stencil, const CommandBufferList& secondaryCBs);
    inline void BeginRenderPass(RenderPass* renderPass, FrameBuffer* fbo, const Rect& renderArea, const ColorList& colors, float depth, uint32_t stencil);
    inline void BeginRenderPass(RenderPass* renderPass, FrameBuffer* fbo, const Rect& renderArea, const Color* colors, float depth, uint32_t stencil);

    inline void Draw(InputAssembler* ia);
    inline void CopyBuffersToTexture(const BufferDataList& buffers, Texture* texture, const BufferTextureCopyList& regions);

    inline void BlitTexture(Texture* srcTexture, Texture* dstTexture, const TextureBlitList& regions, Filter filter);

    inline void PipelineBarrier(const GeneralBarrier* barrier);
    inline void PipelineBarrier(const GeneralBarrier* barrier, const BufferBarrierList& bufferBarriers, const BufferList& buffers, const TextureBarrierList& textureBarriers, const TextureList& textures);

    inline Queue* GetQueue() const { return _queue; }
    inline CommandBufferType GetType() const { return _type; }

    virtual uint32_t GetNumDrawCalls() const { return _numDrawCalls; }
    virtual uint32_t GetNumInstances() const { return _numInstances; }
    virtual uint32_t GetNumTris() const { return _numTriangles; }

protected:
    virtual void DoInit(const CommandBufferInfo& info) = 0;
    virtual void DoDestroy() = 0;

    Queue* _queue = nullptr;
    CommandBufferType _type = CommandBufferType::PRIMARY;

    uint32_t _numDrawCalls = 0;
    uint32_t _numInstances = 0;
    uint32_t _numTriangles = 0;
};

}