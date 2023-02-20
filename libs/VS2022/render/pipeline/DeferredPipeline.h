#pragma once

#include "RenderPipeline.h"

namespace ll
{

    class ClusterLightCulling;

class DeferredPipeline : public RenderPipeline
{
public:
    DeferredPipeline();
    ~DeferredPipeline() override;

    bool Initialize(const RenderPipelineInfo& info) override;
    bool Destroy() override;
    bool Activate(Swapchain* swapchain) override;
    void Render(const std::vector<Camera*>& cameras) override;
    void OnGlobalPipelineStateChanged() override;

    inline Buffer* GetLightsUBO() const { return _lightsUBO; }
    inline const LightList& GetValidLights() const { return _validLights; }
    inline const BufferList& GetLightBuffers() const { return _lightBuffers; }
    inline const UintList& GetLightIndexOffsets() const { return _lightIndexOffsets; }
    inline const UintList& GetLightIndices() const { return _lightIndices; }

private:
    bool ActiveRenderer(Swapchain* swapchain);

    Buffer* _lightsUBO = nullptr;
    LightList _validLights;
    BufferList _lightBuffers;
    UintList _lightIndexOffsets;
    UintList _lightIndices;

    ClusterLightCulling* _clusterComp{ nullptr };

public:
    static constexpr uint32_t GBUFFER_COUNT = 3;

    static StringHandle fgStrHandleGbufferTexture[GBUFFER_COUNT];

    static StringHandle fgStrHandleGbufferPass;
    static StringHandle fgStrHandleLightingPass;
    static StringHandle fgStrHandleTransparentPass;
    static StringHandle fgStrHandleSsprPass;
};

}