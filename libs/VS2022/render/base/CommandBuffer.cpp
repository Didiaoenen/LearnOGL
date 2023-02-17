#include "CommandBuffer.h"

ll::CommandBuffer::CommandBuffer()
{
}

ll::CommandBuffer::~CommandBuffer()
{
}

void ll::CommandBuffer::Initialize(const CommandBufferInfo& info)
{
}

void ll::CommandBuffer::Destroy()
{
}

inline void ll::CommandBuffer::Begin()
{
}

inline void ll::CommandBuffer::Begin(RenderPass* renderPass)
{
}

inline void ll::CommandBuffer::Begin(RenderPass* renderPass, uint32_t subpass)
{
}

inline void ll::CommandBuffer::UpdateBuffer(Buffer* buff, const void* data)
{
}

inline void ll::CommandBuffer::Execute(const CommandBufferList& cmdBuffs, uint32_t count)
{
}

inline void ll::CommandBuffer::BindDescriptorSet(uint32_t set, DescriptorSet* descriptorSet)
{
}

inline void ll::CommandBuffer::BindDescriptorSet(uint32_t set, DescriptorSet* descriptorSet, const std::vector<uint32_t>& dynamicOffsets)
{
}

inline void ll::CommandBuffer::BeginRenderPass(RenderPass* renderPass, FrameBuffer* fbo, const Rect& renderArea, const ColorList& colors, float depth, uint32_t stencil, const CommandBufferList& secondaryCBs)
{
}

inline void ll::CommandBuffer::BeginRenderPass(RenderPass* renderPass, FrameBuffer* fbo, const Rect& renderArea, const ColorList& colors, float depth, uint32_t stencil)
{
}

inline void ll::CommandBuffer::BeginRenderPass(RenderPass* renderPass, FrameBuffer* fbo, const Rect& renderArea, const Color* colors, float depth, uint32_t stencil)
{
}

inline void ll::CommandBuffer::Draw(InputAssembler* ia)
{
}

inline void ll::CommandBuffer::CopyBuffersToTexture(const BufferDataList& buffers, Texture* texture, const BufferTextureCopyList& regions)
{
}

inline void ll::CommandBuffer::BlitTexture(Texture* srcTexture, Texture* dstTexture, const TextureBlitList& regions, Filter filter)
{
}

inline void ll::CommandBuffer::PipelineBarrier(const GeneralBarrier* barrier)
{
}

inline void ll::CommandBuffer::PipelineBarrier(const GeneralBarrier* barrier, const BufferBarrierList& bufferBarriers, const BufferList& buffers, const TextureBarrierList& textureBarriers, const TextureList& textures)
{
}
