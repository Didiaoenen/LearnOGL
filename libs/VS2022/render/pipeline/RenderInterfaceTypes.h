#pragma once

#include "Def_common.h"
#include "PassUtils.h"
#include "RenderGraphTypes.h"
#include "LayoutGraphTypes.h"
#include "RenderCommonTypes.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace ll
{

    class Model;
    class Camera;
    class Device;
    class Material;
    class RenderScene;
    class RenderWindow;
    class PipelineState;
    class InputAssembler;

    class DescriptorSet;
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

class Setter
{
public:
    Setter() noexcept = default;
    Setter(Setter&& rhs) = delete;
    Setter(Setter const& rhs) = delete;
    Setter& operator=(Setter&& rhs) = delete;
    Setter& operator=(Setter const& rhs) = delete;

    virtual ~Setter() noexcept = default;

    virtual void setMat4(const std::string& name, const glm::mat4& mat) = 0;
    virtual void setQuaternion(const std::string& name, const glm::quat& quat) = 0;
    virtual void setColor(const std::string& name, const Color& color) = 0;
    virtual void setVec4(const std::string& name, const glm::vec4& vec) = 0;
    virtual void setVec2(const std::string& name, const glm::vec2& vec) = 0;
    virtual void setFloat(const std::string& name, float v) = 0;

    virtual void setBuffer(const std::string& name, Buffer* buffer) = 0;
    virtual void setTexture(const std::string& name, Texture* texture) = 0;
    virtual void setReadWriteBuffer(const std::string& name, Buffer* buffer) = 0;
    virtual void setReadWriteTexture(const std::string& name, Texture* texture) = 0;
    virtual void setSampler(const std::string& name, Sampler* sampler) = 0;
};

class ComputeQueueBuilder : public Setter {
public:
    ComputeQueueBuilder() noexcept = default;

    virtual void addDispatch(const std::string& shader, uint32_t threadGroupCountX, uint32_t threadGroupCountY, uint32_t threadGroupCountZ, const std::string& name) = 0;
    virtual void addDispatch(const std::string& shader, uint32_t threadGroupCountX, uint32_t threadGroupCountY, uint32_t threadGroupCountZ) = 0;
};

class ComputePassBuilder : public Setter 
{
public:
    ComputePassBuilder() noexcept = default;

    virtual void addComputeView(const std::string& name, const ComputeView& view) = 0;

    virtual ComputeQueueBuilder* addQueue(const std::string& name) = 0;
    virtual ComputeQueueBuilder* addQueue() = 0;

    virtual void addDispatch(const std::string& shader, uint32_t threadGroupCountX, uint32_t threadGroupCountY, uint32_t threadGroupCountZ, const std::string& name) = 0;
    virtual void addDispatch(const std::string& shader, uint32_t threadGroupCountX, uint32_t threadGroupCountY, uint32_t threadGroupCountZ) = 0;
};

class MovePassBuilder 
{
public:
    MovePassBuilder() noexcept = default;
    MovePassBuilder(MovePassBuilder&& rhs) = delete;
    MovePassBuilder(MovePassBuilder const& rhs) = delete;
    MovePassBuilder& operator=(MovePassBuilder&& rhs) = delete;
    MovePassBuilder& operator=(MovePassBuilder const& rhs) = delete;

    virtual ~MovePassBuilder() noexcept = default;

    virtual void addPair(const MovePair& pair) = 0;
};

class CopyPassBuilder 
{
public:
    CopyPassBuilder() noexcept = default;
    CopyPassBuilder(CopyPassBuilder&& rhs) = delete;
    CopyPassBuilder(CopyPassBuilder const& rhs) = delete;
    CopyPassBuilder& operator=(CopyPassBuilder&& rhs) = delete;
    CopyPassBuilder& operator=(CopyPassBuilder const& rhs) = delete;

    virtual ~CopyPassBuilder() noexcept = default;

    virtual void addPair(const CopyPair& pair) = 0;
};

class SceneVisitor 
{
public:
    SceneVisitor() noexcept = default;
    SceneVisitor(SceneVisitor&& rhs) = delete;
    SceneVisitor(SceneVisitor const& rhs) = delete;
    SceneVisitor& operator=(SceneVisitor&& rhs) = delete;
    SceneVisitor& operator=(SceneVisitor const& rhs) = delete;

    virtual ~SceneVisitor() noexcept = default;

    virtual const PipelineSceneData* getPipelineSceneData() const = 0;

    virtual void setViewport(const Viewport& vp) = 0;
    virtual void setScissor(const Rect& rect) = 0;
    virtual void bindPipelineState(PipelineState* pso) = 0;
    virtual void bindDescriptorSet(uint32_t set, DescriptorSet* descriptorSet, uint32_t dynamicOffsetCount, const uint32_t* dynamicOffsets) = 0;
    virtual void bindInputAssembler(InputAssembler* ia) = 0;
    virtual void updateBuffer(Buffer* buff, const void* data, uint32_t size) = 0;
    virtual void draw(const DrawInfo& info) = 0;
};

class SceneTask 
{
public:
    SceneTask() noexcept = default;
    SceneTask(SceneTask&& rhs) = delete;
    SceneTask(SceneTask const& rhs) = delete;
    SceneTask& operator=(SceneTask&& rhs) = delete;
    SceneTask& operator=(SceneTask const& rhs) = delete;

    virtual ~SceneTask() noexcept = default;

    virtual TaskType getTaskType() const noexcept = 0;
    virtual void     start() = 0;
    virtual void     join() = 0;
    virtual void     submit() = 0;
};

class SceneTransversal 
{
public:
    SceneTransversal() noexcept = default;
    SceneTransversal(SceneTransversal&& rhs) = delete;
    SceneTransversal(SceneTransversal const& rhs) = delete;
    SceneTransversal& operator=(SceneTransversal&& rhs) = delete;
    SceneTransversal& operator=(SceneTransversal const& rhs) = delete;

    virtual ~SceneTransversal() noexcept = default;

    virtual SceneTask* transverse(SceneVisitor* visitor) const = 0;
};

class LayoutGraphBuilder 
{
public:
    LayoutGraphBuilder() noexcept = default;
    LayoutGraphBuilder(LayoutGraphBuilder&& rhs) = delete;
    LayoutGraphBuilder(LayoutGraphBuilder const& rhs) = delete;
    LayoutGraphBuilder& operator=(LayoutGraphBuilder&& rhs) = delete;
    LayoutGraphBuilder& operator=(LayoutGraphBuilder const& rhs) = delete;

    virtual ~LayoutGraphBuilder() noexcept = default;

    virtual void clear() = 0;
    virtual uint32_t addRenderStage(const std::string& name) = 0;
    virtual uint32_t addRenderPhase(const std::string& name, uint32_t parentID) = 0;
    virtual void addShader(const std::string& name, uint32_t parentPhaseID) = 0;
    virtual void addDescriptorBlock(uint32_t nodeID, const DescriptorBlockIndex& index, const DescriptorBlockFlattened& block) = 0;
    virtual void addUniformBlock(uint32_t nodeID, const DescriptorBlockIndex& index, const std::string& name, const UniformBlock& uniformBlock) = 0;
    virtual void reserveDescriptorBlock(uint32_t nodeID, const DescriptorBlockIndex& index, const DescriptorBlockFlattened& block) = 0;
    virtual int compile() = 0;

    virtual std::string print() const = 0;
};

class RasterQueueBuilder : public Setter
{
public:
    RasterQueueBuilder() noexcept = default;

    virtual void addSceneOfCamera(Camera* camera, LightInfo light, SceneFlags sceneFlags, const std::string& name) = 0;
    virtual void addSceneOfCamera(Camera* camera, LightInfo light, SceneFlags sceneFlags) = 0;
    virtual void addScene(const std::string& name, SceneFlags sceneFlags) = 0;
    virtual void addFullscreenQuad(Material* material, SceneFlags sceneFlags, const std::string& name) = 0;
    virtual void addFullscreenQuad(Material* material, SceneFlags sceneFlags) = 0;
    virtual void addCameraQuad(Camera* camera, Material* material, SceneFlags sceneFlags, const std::string& name) = 0;
    virtual void addCameraQuad(Camera* camera, Material* material, SceneFlags sceneFlags) = 0;
    virtual void clearRenderTarget(const std::string& name, const Color& color) = 0;
    virtual void setViewport(const Viewport& viewport) = 0;
};

class RasterPassBuilder : public Setter
{
public:
    RasterPassBuilder() noexcept = default;

    virtual void addRasterView(const std::string& name, const RasterView& view) = 0;
    virtual void addComputeView(const std::string& name, const ComputeView& view) = 0;
    virtual RasterQueueBuilder* addQueue(QueueHint hint, const std::string& name) = 0;
    virtual RasterQueueBuilder* addQueue(QueueHint hint) = 0;
    virtual void addFullscreenQuad(Material* material, SceneFlags sceneFlags, const std::string& name) = 0;
    virtual void addFullscreenQuad(Material* material, SceneFlags sceneFlags) = 0;
    virtual void addCameraQuad(Camera* camera, Material* material, SceneFlags sceneFlags, const std::string& name) = 0;
    virtual void addCameraQuad(Camera* camera, Material* material, SceneFlags sceneFlags) = 0;
    virtual void setViewport(const Viewport& viewport) = 0;
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