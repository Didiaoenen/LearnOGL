#pragma once

#include "RenderPipeline.h"

namespace ll
{

class ForwardPipeline : public RenderPipeline
{
public:
    ForwardPipeline();
    ~ForwardPipeline() override = default;

    bool Initialize(const RenderPipelineInfo& info) override;
    bool Destroy() override;
    bool Activate(Swapchain* swapchain) override;
    void Render(const std::vector<Camera*>& cameras) override;

    inline const LightList& GetValidLights() const { return _validLights; }
    inline const BufferList& GetLightBuffers() const { return _lightBuffers; }
    inline const UintList& GetLightIndexOffsets() const { return _lightIndexOffsets; }
    inline const UintList& GetLightIndices() const { return _lightIndices; }

    static std::string fgStrHandleForwardPass;

private:
    bool ActiveRenderer(Swapchain* swapchain);

    LightList _validLights;
    BufferList _lightBuffers;
    UintList _lightIndexOffsets;
    UintList _lightIndices;
};

}