#pragma once

#include "Define.h"
#include "CSMLayers.h"

#include "../base/Device.h"
#include "../core/Material.h"

#include <map>

namespace ll
{

    class Fog;
    class Pass;
    class Skybox;
    class Octree;
    class Ambient;
    class Shadows;
    class FrameBuffer;

class PipelineSceneData
{
public:
    PipelineSceneData();
    ~PipelineSceneData();
    virtual void Activate(ll::Device* device);
    void Destroy();

    virtual void UpdatePipelineSceneData() {}

    inline void SetShadowFramebuffer(const Light* light, FrameBuffer* framebuffer) { _shadowFrameBufferMap[light] = framebuffer; }
    inline const std::map<const Light*, IntrusivePtr<FrameBuffer>>& GetShadowFramebufferMap() const { return _shadowFrameBufferMap; }
    inline const RenderObjectList& GetRenderObjects() const { return _renderObjects; }
    inline void SetRenderObjects(RenderObjectList&& ro) { _renderObjects = std::forward<RenderObjectList>(ro); }
    inline const std::vector<const Light*>& GetValidPunctualLights() const { return _validPunctualLights; }
    inline bool IsHDR() const { return _isHDR; }
    inline void SetHDR(bool val) { _isHDR = val; }
    inline Shadows* GetShadows() const { return _shadow; }
    inline CSMLayers* GetCSMLayers() const { return _csmLayers; }
    inline Ambient* GetAmbient() const { return _ambient; }
    inline Skybox* GetSkybox() const { return _skybox; }
    inline Fog* GetFog() const { return _fog; }
    inline Octree* GetOctree() const { return _octree; }
    inline InputAssembler* GetOcclusionQueryInputAssembler() const { return _occlusionQueryInputAssembler; }
    inline Pass* GetOcclusionQueryPass() const { return _occlusionQueryPass; }
    inline Shader* GetOcclusionQueryShader() const { return _occlusionQueryShader; }
    inline const std::vector<IntrusivePtr<Material>>& GetGeometryRendererMaterials() const { return _geometryRendererMaterials; }
    inline const std::vector<Pass*>& GetGeometryRendererPasses() const { return _geometryRendererPasses; }
    inline const std::vector<Shader*>& GetGeometryRendererShaders() const { return _geometryRendererShaders; }
    inline Pass* GetDebugRendererPass() const { return _debugRendererPass; }
    inline Shader* GetDebugRendererShader() const { return _debugRendererShader; }
    inline void AddRenderObject(RenderObject&& obj) { _renderObjects.emplace_back(obj); }
    inline void ClearRenderObjects() { _renderObjects.clear(); }
    inline void AddValidPunctualLight(Light* light) { _validPunctualLights.emplace_back(light); }
    inline void ClearValidPunctualLights() { _validPunctualLights.clear(); }
    inline float GetShadingScale() const { return _shadingScale; }
    inline void SetShadingScale(float val) { _shadingScale = val; }
    inline bool GetCSMSupported() const { return _csmSupported; }
    inline void SetCSMSupported(bool val) { _csmSupported = val; }

protected:
    void InitOcclusionQuery();
    void InitGeometryRenderer();
    void InitDebugRenderer();
    InputAssembler* CreateOcclusionQueryIA();

    static constexpr uint32_t GEOMETRY_RENDERER_TECHNIQUE_COUNT{ 6 };

    IntrusivePtr<Buffer> _occlusionQueryVertexBuffer;
    IntrusivePtr<Buffer> _occlusionQueryIndicesBuffer;
    IntrusivePtr<InputAssembler> _occlusionQueryInputAssembler;
    IntrusivePtr<Material> _occlusionQueryMaterial{ nullptr };
    IntrusivePtr<Material> _debugRendererMaterial{ nullptr };

    Shader* _occlusionQueryShader{ nullptr };
    Pass* _occlusionQueryPass{ nullptr };
    Shader* _debugRendererShader{ nullptr };
    Pass* _debugRendererPass{ nullptr };
    Device* _device{ nullptr };
    Fog* _fog{ nullptr };
    Ambient* _ambient{ nullptr };
    Skybox* _skybox{ nullptr };
    Shadows* _shadow{ nullptr };
    Octree* _octree{ nullptr };
    CSMLayers* _csmLayers{ nullptr };

    bool _isHDR{ true };
    bool _csmSupported{ true };

    float _shadingScale{ 1.0F };

    RenderObjectList _renderObjects;

    std::vector<IntrusivePtr<Material>> _geometryRendererMaterials;
    std::vector<const Light*> _validPunctualLights;
    std::vector<Pass*> _geometryRendererPasses;
    std::vector<Shader*> _geometryRendererShaders;

    std::map<const Light*, IntrusivePtr<FrameBuffer>> _shadowFrameBufferMap;
};

}