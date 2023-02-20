#pragma once

#include "Device.h"

#include <algorithm>

namespace ll
{

class glDevice final : public Device
{
public:
    static glDevice* GetInstance();

    ~glDevice() override;

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

    inline const BindingMapping& BindingMappings() const { return _bindingMappings; }

    inline GPUContext* Context() const { return _gpuContext; }
    inline GPUStateCache* StateCache() const { return _gpuStateCache; }
    inline GPUBlitManager* BlitManager() const { return _gpuBlitManager; }
    inline GPUFramebufferHub* FramebufferHub() const { return _gpuFramebufferHub; }
    inline GPUConstantRegistry* ConstantRegistry() const { return _gpuConstantRegistry; }
    inline GPUFramebufferCacheMap* FramebufferCacheMap() const { return _gpuFramebufferCacheMap; }

    inline bool CheckExtension(const std::string& extension) const 
    {
        return std::any_of(_extensions.begin(), _extensions.end(), [&extension](auto& ext) 
            {
                return ext.find(extension) != ccstd::string::npos;
            });
    }

    inline uint8_t* GetStagingBuffer(uint32_t size = 0) 
    {
        if (size > _stagingBufferSize) {
            CC_FREE(_stagingBuffer);
            _stagingBuffer = static_cast<uint8_t*>(CC_MALLOC(size));
            _stagingBufferSize = size;
        }

        return _stagingBuffer;
    }

    inline bool IsTextureExclusive(const Format& format) { return _textureExclusive[static_cast<size_t>(format)]; };

protected:
    static glDevice* instance;

    friend class DeviceManager;

    glDevice();

    bool DoInit(const DeviceInfo& info) override;
    void DoDestroy() override;
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

    Sampler* CreateSampler(const SamplerInfo& info) override;

    void CopyBuffersToTexture(const uint8_t* const* buffers, Texture* dst, const BufferTextureCopy* regions, uint32_t count) override;
    void CopyTextureToBuffers(Texture* src, uint8_t* const* buffers, const BufferTextureCopy* region, uint32_t count) override;
    void GetQueryPoolResults(QueryPool* queryPool) override {}

    void BindContext(bool bound) override;

    void InitFormatFeature();

    GPUContext* _gpuContext{ nullptr };
    GPUStateCache* _gpuStateCache{ nullptr };
    GPUBlitManager* _gpuBlitManager{ nullptr };
    GPUFramebufferHub* _gpuFramebufferHub{ nullptr };
    GPUConstantRegistry* _gpuConstantRegistry{ nullptr };
    GPUFramebufferCacheMap* _gpuFramebufferCacheMap{ nullptr };

    std::vector<GPUSwapchain*> _swapchains;

    std::array<bool, static_cast<size_t>(Format::COUNT)> _textureExclusive;

    BindingMapping _bindingMappings;

    std::vector<std::string> _extensions;

    uint8_t* _stagingBuffer{ nullptr };
    uint32_t _stagingBufferSize{ 0 };
};

}

