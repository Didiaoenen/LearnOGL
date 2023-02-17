#include "RenderPass.h"

ll::RenderPass::RenderPass()
{
}

ll::RenderPass::~RenderPass()
{
}

void ll::RenderPass::Initialize(const RenderPassInfo& info)
{
    _colorAttachments = info.colorAttachments;
    _depthStencilAttachment = info.depthStencilAttachment;
    _subpasses = info.subpasses;
    _dependencies = info.dependencies;

    DoInit(info);
}

void ll::RenderPass::Destroy()
{
}
