#pragma once

#include "Agent.h"
#include "Device.h"

#include <string>
#include <unordered_set>

namespace ll
{

    class MessageQueue;
    class CommandBuffer;
    class CommandBufferAgent;

class DeviceAgent final : public Agent<Device>
{
public:
    static DeviceAgent* GetInstance();
    static constexpr uint32_t MAX_CPU_FRAME_AHEAD = 1;
    static constexpr uint32_t MAX_FRAME_INDEX = MAX_CPU_FRAME_AHEAD + 1;

    ~DeviceAgent() override;

    using Device::CopyBuffersToTexture;
    using Device::CreateBuffer;
    using Device::CreateCommandBuffer;
    using Device::CreateDescriptorSet;
    using Device::CreateDescriptorSetLayout;
    using Device::CreateFramebuffer;
    using Device::CreateGeneralBarrier;
    using Device::CreateInputAssembler;
    using Device::CreatePipelineLayout;
    using Device::CreatePipelineState;
    using Device::CreateQueryPool;
    using Device::CreateQueue;
    using Device::CreateRenderPass;
    using Device::CreateSampler;
    using Device::CreateShader;
    using Device::CreateTexture;
    using Device::CreateTextureBarrier;

    void Acquire(Swapchain* const* swapchains, uint32_t count) override;
    void Present() override;

    CommandBuffer* CreateCommandBuffer(const CommandBufferInfo& info, bool hasAgent) override;
    Queue* CreateQueue() override;
    QueryPool* CreateQueryPool() override;
    Swapchain* CreateSwapchain() override;
    Buffer* CreateBuffer() override;
    Texture* CreateTexture() override;
    Shader* CreateShader() override;
    InputAssembler* CreateInputAssembler() override;
    RenderPass* CreateRenderPass() override;
    FrameBuffer* CreateFramebuffer() override;
    DescriptorSet* CreateDescriptorSet() override;
    DescriptorSetLayout* CreateDescriptorSetLayout() override;
    PipelineLayout* CreatePipelineLayout() override;
    PipelineState* CreatePipelineState() override;

    Sampler* GetSampler(const SamplerInfo& info) override;
    GeneralBarrier* GetGeneralBarrier(const GeneralBarrierInfo& info) override;
    TextureBarrier* GetTextureBarrier(const TextureBarrierInfo& info) override;

    void CopyBuffersToTexture(const uint8_t* const* buffers, Texture* dst, const BufferTextureCopy* regions, uint32_t count) override;
    void CopyTextureToBuffers(Texture* src, uint8_t* const* buffers, const BufferTextureCopy* region, uint32_t count) override;
    void FlushCommands(CommandBuffer* const* cmdBuffs, uint32_t count) override;
    void GetQueryPoolResults(QueryPool* queryPool) override;
    MemoryStatus& GetMemoryStatus() override { return _actor->GetMemoryStatus(); }
    uint32_t GetNumDrawCalls() const override { return _actor->GetNumDrawCalls(); }
    uint32_t GetNumInstances() const override { return _actor->GetNumInstances(); }
    uint32_t GetNumTris() const override { return _actor->GetNumTris(); }

    uint32_t GetCurrentIndex() const { return _currentIndex; }
    void SetMultithreaded(bool multithreaded);

    inline MessageQueue* GetMessageQueue() const { return _mainMessageQueue; }

    void PresentWait();
    void PresentSignal();
protected:
    static DeviceAgent* instance;

    friend class DeviceManager;
    friend class CommandBufferAgent;

    explicit DeviceAgent(Device* device);

    bool DoInit(const DeviceInfo& info) override;
    void DoDestroy() override;

    bool _multithreaded{ false };
    MessageQueue* _mainMessageQueue{ nullptr };

    uint32_t _currentIndex = 0U;
    //Semaphore _frameBoundarySemaphore{ MAX_CPU_FRAME_AHEAD };

    std::unordered_set<CommandBufferAgent*> _cmdBuffRefs;
};

}