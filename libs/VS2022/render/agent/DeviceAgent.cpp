#include "DeviceAgent.h"

namespace ll
{
    DeviceAgent* DeviceAgent::instance = nullptr;
}

ll::DeviceAgent* ll::DeviceAgent::GetInstance()
{
    return nullptr;
}

ll::DeviceAgent::~DeviceAgent()
{
}

void ll::DeviceAgent::Acquire(Swapchain* const* swapchains, uint32_t count)
{
}

void ll::DeviceAgent::Present()
{
}

ll::CommandBuffer* ll::DeviceAgent::CreateCommandBuffer(const CommandBufferInfo& info, bool hasAgent)
{
    return nullptr;
}

ll::Queue* ll::DeviceAgent::CreateQueue()
{
    return nullptr;
}

ll::QueryPool* ll::DeviceAgent::CreateQueryPool()
{
    return nullptr;
}

ll::Swapchain* ll::DeviceAgent::CreateSwapchain()
{
    return nullptr;
}

ll::Buffer* ll::DeviceAgent::CreateBuffer()
{
    return nullptr;
}

ll::Texture* ll::DeviceAgent::CreateTexture()
{
    return nullptr;
}

ll::Shader* ll::DeviceAgent::CreateShader()
{
    return nullptr;
}

ll::InputAssembler* ll::DeviceAgent::CreateInputAssembler()
{
    return nullptr;
}

ll::RenderPass* ll::DeviceAgent::CreateRenderPass()
{
    return nullptr;
}

ll::FrameBuffer* ll::DeviceAgent::CreateFramebuffer()
{
    return nullptr;
}

ll::DescriptorSet* ll::DeviceAgent::CreateDescriptorSet()
{
    return nullptr;
}

ll::DescriptorSetLayout* ll::DeviceAgent::CreateDescriptorSetLayout()
{
    return nullptr;
}

ll::PipelineLayout* ll::DeviceAgent::CreatePipelineLayout()
{
    return nullptr;
}

ll::PipelineState* ll::DeviceAgent::CreatePipelineState()
{
    return nullptr;
}

ll::Sampler* ll::DeviceAgent::GetSampler(const SamplerInfo& info)
{
    return nullptr;
}

ll::GeneralBarrier* ll::DeviceAgent::GetGeneralBarrier(const GeneralBarrierInfo& info)
{
    return nullptr;
}

ll::TextureBarrier* ll::DeviceAgent::GetTextureBarrier(const TextureBarrierInfo& info)
{
    return nullptr;
}

void ll::DeviceAgent::CopyBuffersToTexture(const uint8_t* const* buffers, Texture* dst, const BufferTextureCopy* regions, uint32_t count)
{
}

void ll::DeviceAgent::CopyTextureToBuffers(Texture* src, uint8_t* const* buffers, const BufferTextureCopy* region, uint32_t count)
{
}

void ll::DeviceAgent::FlushCommands(CommandBuffer* const* cmdBuffs, uint32_t count)
{
}

void ll::DeviceAgent::GetQueryPoolResults(QueryPool* queryPool)
{
}

void ll::DeviceAgent::SetMultithreaded(bool multithreaded)
{
}

void ll::DeviceAgent::PresentWait()
{
}

void ll::DeviceAgent::PresentSignal()
{
}

ll::DeviceAgent::DeviceAgent(Device* device) 
    : Agent(device) 
{
    ll::DeviceAgent::instance = this;
}

bool ll::DeviceAgent::DoInit(const DeviceInfo& info)
{
    return false;
}

void ll::DeviceAgent::DoDestroy()
{
}
