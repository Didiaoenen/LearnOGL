#include "DeferredPipeline.h"

ll::DeferredPipeline::DeferredPipeline()
{
}

ll::DeferredPipeline::~DeferredPipeline()
{
}

bool ll::DeferredPipeline::Initialize(const RenderPipelineInfo& info)
{
    return false;
}

bool ll::DeferredPipeline::Destroy()
{
    return false;
}

bool ll::DeferredPipeline::Activate(Swapchain* swapchain)
{
    return false;
}

void ll::DeferredPipeline::Render(const std::vector<Camera*>& cameras)
{
}

void ll::DeferredPipeline::OnGlobalPipelineStateChanged()
{
}

bool ll::DeferredPipeline::ActiveRenderer(Swapchain* swapchain)
{
    return false;
}
