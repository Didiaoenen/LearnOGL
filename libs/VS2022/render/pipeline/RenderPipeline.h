#pragma once

#include "Def_common.h"
#include "Define.h"
#include "PassUtils.h"
#include "FrameGraph.h"

#include <unordered_map>

namespace ll
{
    class CommandBuffer;
    class DescriptorSet;
    class DescriptorSetLayout;
    
    class Device;
    class Camera;
    class SubModel;

    class PipelineUBO;
    class RenderStage;
    class GlobalDSManager;
    class GeometryRenderer;
    class PipelineSceneData;

struct RenderPipelineInfo 
{
    uint32_t tag = 0;
    RenderFlowList flows;
};

class RenderPipeline
{
public:
    static RenderPipeline* GetInstance();
    static Rect GetRenderArea(Camera* camera);

    RenderPipeline();
    virtual ~RenderPipeline();
    bool Destroy();

    virtual bool Activate(Swapchain* swapchain);
    virtual bool Initialize(const RenderPipelineInfo& info);
    virtual void Render(const std::vector<Camera*>& cameras);
    virtual void OnGlobalPipelineStateChanged();

    inline const RenderFlowList& GetFlows() const { return _flows; }
    inline uint32_t GetTag() const { return _tag; }
    inline const std::unordered_map<std::string, InternalBindingInst>& GetGlobalBindings() const { return _globalBindings; }
    inline const MacroRecord& GetMacros() const { return _macros; }
    inline void SetValue(const std::string& name, int32_t value) { _macros[name] = value; }
    inline void SetValue(const std::string& name, bool value) { _macros[name] = value; }
    inline void SetValue(const std::string& name, const std::string& value) { _macros[name] = value; }
    inline GlobalDSManager* GetGlobalDSManager() const { return _globalDSManager; }
    inline DescriptorSet* GetDescriptorSet() const { return _descriptorSet; }
    inline PipelineSceneData* GetPipelineSceneData() const { return _pipelineSceneData; }
    inline const CommandBufferList& GetCommandBuffers() const { return _commandBuffers; }
    inline const QueryPoolList& GetQueryPools() const { return _queryPools; }
    inline PipelineUBO* GetPipelineUBO() const { return _pipelineUBO; }
    inline const std::string& GetConstantMacros() const { return _constantMacros; }
    inline Device* GetDevice() const { return _device; }
    bool IsOcclusionQueryEnabled() const { return false; }
    void SetOcclusionQueryEnabled(bool enable) { _occlusionQueryEnabled = enable; }
    
    DescriptorSetLayout* GetDescriptorSetLayout() const;
    RenderStage* GetRenderstageByName(const std::string& name) const;
    bool IsOccluded(const Camera* camera, const SubModel* subModel);
    bool IsEnvmapEnabled() const;
    Viewport GetViewport(Camera* camera);
    Rect GetScissor(Camera* camera);
    void GenQuadVertexData(const Vec4& viewport, float* data);
    uint32_t GetWidth() const { return _width; }
    uint32_t GetHeight() const { return _height; }
    FrameGraph& GetFrameGraph() { return _fg; }
    Color GetClearcolor(Camera* camera) const;
    InputAssembler* GetIAByRenderArea(const Rect& renderArea);
    void UpdateQuadVertexData(const Vec4& viewport, Buffer* buffer);
    void EnsureEnoughSize(const std::vector<Camera*>& cameras);
    bool OreateQuadInputAssembler(Buffer* quadIB, Buffer** quadVB, InputAssembler** quadIA);

    float GetShadingScale() const;
    void SetShadingScale(float scale);

    inline Model* GetProfiler() const { return _profiler; }
    inline void setProfiler(Model* value) { _profiler = value; }

    inline bool IsClusterEnabled() const { return _clusterEnabled; }
    inline void SetClusterEnabled(bool enable) { _clusterEnabled = enable; }

    inline bool IsBloomEnabled() const { return _bloomEnabled; }
    inline void SetBloomEnabled(bool enable) { _bloomEnabled = enable; }

    inline GeometryRenderer* GetGeometryRenderer() const { return nullptr; }

    inline void ResetRenderQueue(bool reset) { _resetRenderQueue = reset; }
    inline bool IsRenderQueueReset() const { return _resetRenderQueue; }

protected:
    static RenderPipeline* instance;

    void GenerateConstantMacros();
    void DestroyQuadInputAssembler();

    static void FramegraphGC();

    CommandBufferList _commandBuffers;
    QueryPoolList _queryPools;
    RenderFlowList _flows;
    std::unordered_map<std::string, InternalBindingInst> _globalBindings;
    MacroRecord _macros;
    uint32_t _tag{ 0 };
    std::string _constantMacros;

    Device* _device{ nullptr };
    GlobalDSManager* _globalDSManager{ nullptr };
    DescriptorSet* _descriptorSet{ nullptr };
    PipelineUBO* _pipelineUBO{ nullptr };
    IntrusivePtr<Model> _profiler;
    IntrusivePtr<PipelineSceneData> _pipelineSceneData;

    uint32_t _width{ 0 };
    uint32_t _height{ 0 };
    Buffer* _quadIB{ nullptr };
    std::vector<Buffer*> _quadVB;
    std::unordered_map<Vec4, InputAssembler*, std::hash<Vec4>> _quadIA;

    FrameGraph _fg;
    std::unordered_map<ClearFlags, RenderPass*> _renderPasses;

    bool _clusterEnabled{ false };
    bool _bloomEnabled{ false };
    bool _occlusionQueryEnabled{ false };

    bool _resetRenderQueue{ true };
};

}