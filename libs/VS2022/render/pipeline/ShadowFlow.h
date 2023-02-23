#pragma once

#include "RenderFlow.h"

namespace ll
{

class FrameBuffer;
class DescriptorSet;

class ShadowFlow : public RenderFlow
{
public:
    ShadowFlow();
    ~ShadowFlow() override;

    static const RenderFlowInfo& GetInitializeInfo();

    bool Initialize(const RenderFlowInfo& info) override;

    void Activate(RenderPipeline* pipeline) override;

    void Render(Camera* camera) override;

    void Destroy() override;

private:
    void RenderStage(DescriptorSet* globalDS, Camera* camera, const Light* light, FrameBuffer* framebuffer, uint32_t level = 0);

    void LightCollecting();

    void ClearShadowMap(Camera* camera);

    void ResizeShadowMap(const Light* light, DescriptorSet* ds);

    void InitShadowFrameBuffer(const RenderPipeline* pipeline, const Light* light);

    static RenderFlowInfo initInfo;

    RenderPass* _renderPass{ nullptr };

    std::vector<const Light*> _validLights;
    std::vector<IntrusivePtr<Texture>> _usedTextures;

    static std::map<uint32_t, IntrusivePtr<RenderPass>> renderPassHashMap;
};

}