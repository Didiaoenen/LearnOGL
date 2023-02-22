#include "glDevice.h"

ll::glDevice* ll::glDevice::GetInstance()
{
    return nullptr;
}

ll::glDevice::~glDevice()
{
}

void ll::glDevice::Acquire(Swapchain* const* swapchains, uint32_t count)
{
}

void ll::glDevice::Present()
{
}

void ll::glDevice::CopyBuffersToTexture(const uint8_t* const* buffers, Texture* dst, const BufferTextureCopy* regions, uint32_t count)
{
}

void ll::glDevice::CopyTextureToBuffers(Texture* src, uint8_t* const* buffers, const BufferTextureCopy* region, uint32_t count)
{
}

void ll::glDevice::BindContext(bool bound)
{
}

void ll::glDevice::InitFormatFeature()
{
}

ll::glDevice::glDevice()
{
}

bool ll::glDevice::DoInit(const DeviceInfo& info)
{
    return false;
}

void ll::glDevice::DoDestroy()
{
}

CommandBuffer* ll::glDevice::CreateCommandBuffer(const CommandBufferInfo& info, bool hasAgent)
{
    return nullptr;
}

Queue* ll::glDevice::CreateQueue()
{
    return nullptr;
}

QueryPool* ll::glDevice::CreateQueryPool()
{
    return nullptr;
}

Swapchain* ll::glDevice::CreateSwapchain()
{
    return nullptr;
}

Buffer* ll::glDevice::CreateBuffer()
{
    return nullptr;
}

Texture* ll::glDevice::CreateTexture()
{
    return nullptr;
}

Shader* ll::glDevice::CreateShader()
{
    return nullptr;
}

InputAssembler* ll::glDevice::CreateInputAssembler()
{
    return nullptr;
}

RenderPass* ll::glDevice::CreateRenderPass()
{
    return nullptr;
}

FrameBuffer* ll::glDevice::CreateFramebuffer()
{
    return nullptr;
}

DescriptorSet* ll::glDevice::CreateDescriptorSet()
{
    return nullptr;
}

DescriptorSetLayout* ll::glDevice::CreateDescriptorSetLayout()
{
    return nullptr;
}

PipelineLayout* ll::glDevice::CreatePipelineLayout()
{
    return nullptr;
}

PipelineState* ll::glDevice::CreatePipelineState()
{
    return nullptr;
}

Sampler* ll::glDevice::CreateSampler(const SamplerInfo& info)
{
    return nullptr;
}
