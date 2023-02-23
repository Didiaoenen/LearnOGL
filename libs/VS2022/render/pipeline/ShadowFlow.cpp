#include "ShadowFlow.h"

ll::ShadowFlow::ShadowFlow()
{
}

ll::ShadowFlow::~ShadowFlow()
{
}

const ll::RenderFlowInfo& ll::ShadowFlow::GetInitializeInfo()
{
    // TODO: 在此处插入 return 语句
    return {};
}

bool ll::ShadowFlow::Initialize(const RenderFlowInfo& info)
{
    return false;
}

void ll::ShadowFlow::Activate(RenderPipeline* pipeline)
{
}

void ll::ShadowFlow::Render(Camera* camera)
{
}

void ll::ShadowFlow::Destroy()
{
}

void ll::ShadowFlow::RenderStage(DescriptorSet* globalDS, Camera* camera, const Light* light, FrameBuffer* framebuffer, uint32_t level)
{
}

void ll::ShadowFlow::LightCollecting()
{
}

void ll::ShadowFlow::ClearShadowMap(Camera* camera)
{
}

void ll::ShadowFlow::ResizeShadowMap(const Light* light, DescriptorSet* ds)
{
}

void ll::ShadowFlow::InitShadowFrameBuffer(const RenderPipeline* pipeline, const Light* light)
{
}
