#pragma once

#include <string>
#include <vector>

namespace ll
{

    class Model;
    class Device;
    class Camera;
    class Swapchain;
    class CommandBuffer;
    class GlobalDSManager;
    class GeometryRenderer;
    class PipelineSceneData;

class PipelineRuntime 
{
public:
    PipelineRuntime() noexcept = default;
    PipelineRuntime(PipelineRuntime&& rhs) = delete;
    PipelineRuntime(PipelineRuntime const& rhs) = delete;
    PipelineRuntime& operator=(PipelineRuntime&& rhs) = delete;
    PipelineRuntime& operator=(PipelineRuntime const& rhs) = delete;

    virtual ~PipelineRuntime() noexcept = default;

    virtual bool Activate(Swapchain* swapchain) = 0;
    virtual bool Destroy() noexcept = 0;
    virtual void Render(const std::vector<Camera*>& cameras) = 0;

    virtual Device* GetDevice() const = 0;
    virtual const MacroRecord& GetMacros() const = 0;
    virtual GlobalDSManager* GetGlobalDSManager() const = 0;
    virtual DescriptorSetLayout* GetDescriptorSetLayout() const = 0;
    virtual DescriptorSet* GetDescriptorSet() const = 0;
    virtual std::vector<CommandBuffer*> GetCommandBuffers() const = 0;
    virtual PipelineSceneData* GetPipelineSceneData() const = 0;
    virtual const std::string& GetConstantMacros() const = 0;
    virtual Model* GetProfiler() const = 0;
    virtual void SetProfiler(Model* profiler) = 0;
    virtual GeometryRenderer* GetGeometryRenderer() const = 0;

    virtual float GetShadingScale() const = 0;
    virtual void SetShadingScale(float scale) = 0;

    virtual const std::string& GetMacroString(const std::string& name) const = 0;
    virtual int32_t GetMacroInt(const std::string& name) const = 0;
    virtual bool GetMacroBool(const std::string& name) const = 0;

    virtual void SetMacroString(const std::string& name, const std::string& value) = 0;
    virtual void SetMacroInt(const std::string& name, int32_t value) = 0;
    virtual void SetMacroBool(const std::string& name, bool value) = 0;

    virtual void OnGlobalPipelineStateChanged() = 0;

    virtual void SetValue(const std::string& name, int32_t value) = 0;
    virtual void SetValue(const std::string& name, bool value) = 0;

    virtual bool IsOcclusionQueryEnabled() const = 0;

    virtual void ResetRenderQueue(bool reset) = 0;
    virtual bool IsRenderQueueReset() const = 0;
};

class Pipeline : public PipelineRuntime 
{
public:
    Pipeline() noexcept = default;

    virtual bool ContainsResource(const std::string& name) const = 0;
    virtual uint32_t AddRenderTexture(const std::string& name, Format format, uint32_t width, uint32_t height, RenderWindow* renderWindow) = 0;
    virtual uint32_t AddRenderTarget(const std::string& name, Format format, uint32_t width, uint32_t height, ResourceResidency residency) = 0;
    virtual uint32_t AddDepthStencil(const std::string& name, Format format, uint32_t width, uint32_t height, ResourceResidency residency) = 0;

    virtual void BeginFrame() = 0;
    virtual void EndFrame() = 0;
    virtual RasterPassBuilder* AddRasterPass(uint32_t width, uint32_t height, const std::string& layoutName, const std::string& name) = 0;
    virtual RasterPassBuilder* AddRasterPass(uint32_t width, uint32_t height, const std::string& layoutName) = 0;
    virtual ComputePassBuilder* AddComputePass(const std::string& layoutName, const std::string& name) = 0;
    virtual ComputePassBuilder* AddComputePass(const std::string& layoutName) = 0;
    virtual MovePassBuilder* AddMovePass(const std::string& name) = 0;
    virtual CopyPassBuilder* AddCopyPass(const std::string& name) = 0;
    virtual void PresentAll() = 0;

    virtual SceneTransversal* CreateSceneTransversal(const Camera* camera, const RenderScene* scene) = 0;
    virtual LayoutGraphBuilder* GetLayoutGraphBuilder() = 0;
    virtual DescriptorSetLayout* GetDescriptorSetLayout(const std::string& shaderName, UpdateFrequency freq) = 0;
};

}