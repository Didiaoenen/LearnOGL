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

ll::CommandBuffer* ll::glDevice::CreateCommandBuffer(const CommandBufferInfo& info, bool hasAgent)
{
    return nullptr;
}

ll::Queue* ll::glDevice::CreateQueue()
{
    return nullptr;
}

ll::QueryPool* ll::glDevice::CreateQueryPool()
{
    return nullptr;
}

ll::Swapchain* ll::glDevice::CreateSwapchain()
{
    return nullptr;
}

ll::Buffer* ll::glDevice::CreateBuffer()
{
    return nullptr;
}

ll::Texture* ll::glDevice::CreateTexture()
{
    return nullptr;
}

ll::Shader* ll::glDevice::CreateShader()
{
    return nullptr;
}

ll::InputAssembler* ll::glDevice::CreateInputAssembler()
{
    return nullptr;
}

ll::RenderPass* ll::glDevice::CreateRenderPass()
{
    return nullptr;
}

ll::FrameBuffer* ll::glDevice::CreateFramebuffer()
{
    return nullptr;
}

ll::DescriptorSet* ll::glDevice::CreateDescriptorSet()
{
    return nullptr;
}

ll::DescriptorSetLayout* ll::glDevice::CreateDescriptorSetLayout()
{
    return nullptr;
}

ll::PipelineLayout* ll::glDevice::CreatePipelineLayout()
{
    return nullptr;
}

ll::PipelineState* ll::glDevice::CreatePipelineState()
{
    return nullptr;
}

ll::Sampler* ll::glDevice::CreateSampler(const SamplerInfo& info)
{
    return nullptr;
}
