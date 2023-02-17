#include "glPrimaryCommandBuffer.h"

ll::glPrimaryCommandBuffer::~glPrimaryCommandBuffer()
{
}

void ll::glPrimaryCommandBuffer::Begin(RenderPass* renderPass, uint32_t subpass, FrameBuffer* frameBuffer)
{
}

void ll::glPrimaryCommandBuffer::End()
{
}

void ll::glPrimaryCommandBuffer::BeginRenderPass(RenderPass* renderPass, FrameBuffer* fbo, const Rect& renderArea, const Color* colors, float depth, uint32_t stencil, CommandBuffer* const* secondaryCBs, uint32_t secondaryCBCount)
{
}

void ll::glPrimaryCommandBuffer::EndRenderPass()
{
}

void ll::glPrimaryCommandBuffer::NextSubpass()
{
}

void ll::glPrimaryCommandBuffer::Draw(const DrawInfo& info)
{
}

void ll::glPrimaryCommandBuffer::SetViewport(const Viewport& vp)
{
}

void ll::glPrimaryCommandBuffer::SetScissor(const Rect& rect)
{
}

void ll::glPrimaryCommandBuffer::UpdateBuffer(Buffer* buff, const void* data, uint32_t size)
{
}

void ll::glPrimaryCommandBuffer::CopyBuffersToTexture(const uint8_t* const* buffers, Texture* texture, const BufferTextureCopy* regions, uint32_t count)
{
}

void ll::glPrimaryCommandBuffer::BlitTexture(Texture* srcTexture, Texture* dstTexture, const TextureBlit* regions, uint32_t count, Filter filter)
{
}

void ll::glPrimaryCommandBuffer::Execute(CommandBuffer* const* cmdBuffs, uint32_t count)
{
}

void ll::glPrimaryCommandBuffer::BindStates()
{
}
