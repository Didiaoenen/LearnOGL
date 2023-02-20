#pragma once

#include "Def_common.h"
#include "Shader.h"
#include "Sampler.h"
#include "PipelineLayout.h"

namespace ll
{

class Device
{
public:
	static Device* GetInstance();

	virtual ~Device();

	bool Initialize(const DeviceInfo& info);
	void Destroy();

    virtual void Acquire(Swapchain* const* swapchains, uint32_t count) = 0;
    virtual void Present() = 0;

    virtual void FlushCommands(CommandBuffer* const* cmdBuffs, uint32_t count) {}

    virtual MemoryStatus& GetMemoryStatus() { return _memoryStatus; }
    virtual uint32_t GetNumDrawCalls() const { return _numDrawCalls; }
    virtual uint32_t GetNumInstances() const { return _numInstances; }
    virtual uint32_t GetNumTris() const { return _numTriangles; }

    inline CommandBuffer* CreateCommandBuffer(const CommandBufferInfo& info);
    inline Queue* CreateQueue(const QueueInfo& info);
    inline QueryPool* CreateQueryPool(const QueryPoolInfo& info);
    inline Swapchain* CreateSwapchain(const SwapchainInfo& info);
    inline const std::vector<Swapchain*>& GetSwapchains() const { return _swapchains; }
    inline Buffer* CreateBuffer(const BufferInfo& info);
    inline Buffer* CreateBuffer(const BufferViewInfo& info);
    inline Texture* CreateTexture(const TextureInfo& info);
    inline Texture* CreateTexture(const TextureViewInfo& info);
    inline Shader* CreateShader(const ShaderInfo& info);
    inline InputAssembler* CreateInputAssembler(const InputAssemblerInfo& info);
    inline RenderPass* CreateRenderPass(const RenderPassInfo& info);
    inline FrameBuffer* CreateFramebuffer(const FramebufferInfo& info);
    inline DescriptorSet* CreateDescriptorSet(const DescriptorSetInfo& info);
    inline DescriptorSetLayout* CreateDescriptorSetLayout(const DescriptorSetLayoutInfo& info);
    inline PipelineLayout* CreatePipelineLayout(const PipelineLayoutInfo& info);
    inline PipelineState* CreatePipelineState(const PipelineStateInfo& info);

    virtual Sampler* GetSampler(const SamplerInfo& info);
    virtual GeneralBarrier* GetGeneralBarrier(const GeneralBarrierInfo& info);
    virtual TextureBarrier* GetTextureBarrier(const TextureBarrierInfo& info);
    virtual BufferBarrier* GetBufferBarrier(const BufferBarrierInfo& info);

    virtual void CopyBuffersToTexture(const uint8_t* const* buffers, Texture* dst, const BufferTextureCopy* regions, uint32_t count) = 0;
    virtual void CopyTextureToBuffers(Texture* src, uint8_t* const* buffers, const BufferTextureCopy* region, uint32_t count) = 0;
    virtual void GetQueryPoolResults(QueryPool* queryPool) = 0;

    inline void CopyTextureToBuffers(Texture* src, BufferSrcList& buffers, const BufferTextureCopyList& regions);
    inline void CopyBuffersToTexture(const BufferDataList& buffers, Texture* dst, const BufferTextureCopyList& regions);
    inline void FlushCommands(const std::vector<CommandBuffer*>& cmdBuffs);
    inline void Acquire(const std::vector<Swapchain*>& swapchains);

    inline Queue* GetQueue() const { return _queue; }
    inline QueryPool* GetQueryPool() const { return _queryPool; }
    inline CommandBuffer* GetCommandBuffer() const { return _cmdBuff; }
    inline const DeviceCaps& GetCapabilities() const { return _caps; }
    inline API GetGfxAPI() const { return _api; }
    inline const std::string& GetDeviceName() const { return _deviceName; }
    inline const std::string& GetRenderer() const { return _renderer; }
    inline const std::string& GetVendor() const { return _vendor; }
    inline bool HasFeature(Feature feature) const { return _features[toNumber(feature)]; }
    inline FormatFeature GetFormatFeatures(Format format) const { return _formatFeatures[toNumber(format)]; }

    inline const BindingMappingInfo& GetBindingMappingInfo() const { return _bindingMappingInfo; }

    template <typename ExecuteMethod>
    void RegisterOnAcquireCallback(ExecuteMethod&& execute);

    inline void SetOptions(const DeviceOptions& opts) { _options = opts; }
    inline const DeviceOptions& GetOptions() const { return _options; }

protected:
    static Device* instance;
    static bool isSupportDetachDeviceThread;

    friend class DeviceAgent;
    friend class DeviceValidator;
    friend class DeviceManager;

    Device();

    void DestroySurface(void* windowHandle);
    void CreateSurface(void* windowHandle);

    virtual bool DoInit(const DeviceInfo& info) = 0;
    virtual void DoDestroy() = 0;

    virtual CommandBuffer* CreateCommandBuffer(const CommandBufferInfo& info, bool hasAgent) = 0;
    virtual Queue* CreateQueue() = 0;
    virtual QueryPool* CreateQueryPool() = 0;
    virtual Swapchain* CreateSwapchain() = 0;
    virtual Buffer* CreateBuffer() = 0;
    virtual Texture* CreateTexture() = 0;
    virtual Shader* CreateShader() = 0;
    virtual InputAssembler* CreateInputAssembler() = 0;
    virtual RenderPass* CreateRenderPass() = 0;
    virtual FrameBuffer* CreateFramebuffer() = 0;
    virtual DescriptorSet* CreateDescriptorSet() = 0;
    virtual DescriptorSetLayout* CreateDescriptorSetLayout() = 0;
    virtual PipelineLayout* CreatePipelineLayout() = 0;
    virtual PipelineState* CreatePipelineState() = 0;

    virtual Sampler* CreateSampler(const SamplerInfo& info) { return new Sampler(info); }
    virtual GeneralBarrier* CreateGeneralBarrier(const GeneralBarrierInfo& info) { return new GeneralBarrier(info); }
    virtual TextureBarrier* CreateTextureBarrier(const TextureBarrierInfo& info) { return new TextureBarrier(info); }
    virtual BufferBarrier* CreateBufferBarrier(const BufferBarrierInfo& info) { return new BufferBarrier(info); }

    virtual void BindContext(bool bound) {}

    std::string _deviceName;
    std::string _renderer;
    std::string _vendor;
    std::string _version;
    API _api{ API::UNKNOWN };
    DeviceCaps _caps;
    BindingMappingInfo _bindingMappingInfo;
    DeviceOptions _options;

    bool _multithreadedCommandRecording{ true };

    std::array<bool, static_cast<size_t>(Feature::COUNT)> _features;
    std::array<FormatFeature, static_cast<size_t>(Format::COUNT)> _formatFeatures;

    Queue* _queue{ nullptr };
    QueryPool* _queryPool{ nullptr };
    CommandBuffer* _cmdBuff{ nullptr };
    Executable* _onAcquire{ nullptr };

    uint32_t _numDrawCalls{ 0U };
    uint32_t _numInstances{ 0U };
    uint32_t _numTriangles{ 0U };
    MemoryStatus _memoryStatus;

    std::unordered_map<SamplerInfo, Sampler*, Hasher<SamplerInfo>> _samplers;
    std::unordered_map<GeneralBarrierInfo, GeneralBarrier*, Hasher<GeneralBarrierInfo>> _generalBarriers;
    std::unordered_map<TextureBarrierInfo, TextureBarrier*, Hasher<TextureBarrierInfo>> _textureBarriers;
    std::unordered_map<BufferBarrierInfo, BufferBarrier*, Hasher<BufferBarrierInfo>> _bufferBarriers;

private:
    std::vector<Swapchain*> _swapchains;
};

}
