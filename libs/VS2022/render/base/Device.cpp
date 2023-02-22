#include "Device.h"

ll::Device* ll::Device::GetInstance()
{
    return nullptr;
}

ll::Device::~Device()
{
}

bool ll::Device::Initialize(const DeviceInfo& info)
{
    return false;
}

void ll::Device::Destroy()
{
}

inline ll::CommandBuffer* ll::Device::CreateCommandBuffer(const CommandBufferInfo& info)
{
    return nullptr;
}

inline ll::Queue* ll::Device::CreateQueue(const QueueInfo& info)
{
    return nullptr;
}

inline ll::QueryPool* ll::Device::CreateQueryPool(const QueryPoolInfo& info)
{
    return nullptr;
}

inline ll::Swapchain* ll::Device::CreateSwapchain(const SwapchainInfo& info)
{
    return nullptr;
}

inline ll::Buffer* ll::Device::CreateBuffer(const BufferInfo& info)
{
    return nullptr;
}

inline ll::Buffer* ll::Device::CreateBuffer(const BufferViewInfo& info)
{
    return nullptr;
}

inline ll::Texture* ll::Device::CreateTexture(const TextureInfo& info)
{
    return nullptr;
}

inline ll::Texture* ll::Device::CreateTexture(const TextureViewInfo& info)
{
    return nullptr;
}

inline ll::Shader* ll::Device::CreateShader(const ShaderInfo& info)
{
    return nullptr;
}

inline ll::InputAssembler* ll::Device::CreateInputAssembler(const InputAssemblerInfo& info)
{
    return nullptr;
}

inline ll::RenderPass* ll::Device::CreateRenderPass(const RenderPassInfo& info)
{
    return nullptr;
}

inline ll::FrameBuffer* ll::Device::CreateFramebuffer(const FramebufferInfo& info)
{
    return nullptr;
}

inline ll::DescriptorSet* ll::Device::CreateDescriptorSet(const DescriptorSetInfo& info)
{
    return nullptr;
}

inline ll::DescriptorSetLayout* ll::Device::CreateDescriptorSetLayout(const DescriptorSetLayoutInfo& info)
{
    return nullptr;
}

inline ll::PipelineLayout* ll::Device::CreatePipelineLayout(const PipelineLayoutInfo& info)
{
    return nullptr;
}

inline ll::PipelineState* ll::Device::CreatePipelineState(const PipelineStateInfo& info)
{
    return nullptr;
}

ll::Sampler* ll::Device::GetSampler(const SamplerInfo& info)
{
    return nullptr;
}

ll::GeneralBarrier* ll::Device::GetGeneralBarrier(const GeneralBarrierInfo& info)
{
    return nullptr;
}

ll::TextureBarrier* ll::Device::GetTextureBarrier(const TextureBarrierInfo& info)
{
    return nullptr;
}

ll::BufferBarrier* ll::Device::GetBufferBarrier(const BufferBarrierInfo& info)
{
    return nullptr;
}

inline void ll::Device::CopyTextureToBuffers(Texture* src, BufferSrcList& buffers, const BufferTextureCopyList& regions)
{
}

inline void ll::Device::CopyBuffersToTexture(const BufferDataList& buffers, Texture* dst, const BufferTextureCopyList& regions)
{
}

inline void ll::Device::FlushCommands(const std::vector<CommandBuffer*>& cmdBuffs)
{
}

inline void ll::Device::Acquire(const std::vector<Swapchain*>& swapchains)
{
}

ll::Device::Device()
{
}

void ll::Device::DestroySurface(void* windowHandle)
{
}

void ll::Device::CreateSurface(void* windowHandle)
{
}
