#include "glRenderPass.h"

ll::glRenderPass::glRenderPass()
{
}

ll::glRenderPass::~glRenderPass()
{
}

void ll::glRenderPass::DoInit(const RenderPassInfo& info)
{
    _gpuRenderPass = new GPURenderPass;
    _gpuRenderPass->colorAttachments = _colorAttachments;
    _gpuRenderPass->depthStencilAttachment = _depthStencilAttachment;
    _gpuRenderPass->subpasses = _subpasses;

    uint32_t colorCount = toUint(_gpuRenderPass->colorAttachments.size());
    if (_gpuRenderPass->subpasses.empty()) 
    {
        _gpuRenderPass->subpasses.emplace_back();
        auto& subpass = _gpuRenderPass->subpasses.back();
        subpass.colors.resize(_colorAttachments.size());
        for (uint32_t i = 0U; i < _colorAttachments.size(); ++i) 
        {
            subpass.colors[i] = i;
        }
        if (_depthStencilAttachment.format != Format::UNKNOWN) 
        {
            subpass.depthStencil = colorCount;
        }
    }
    else 
    {
        for (auto& subpass : _gpuRenderPass->subpasses) 
        {
            if (subpass.depthStencil != INVALID_BINDING && subpass.depthStencil > colorCount) 
            {
                subpass.depthStencil = colorCount;
            }
            if (subpass.depthStencilResolve != INVALID_BINDING && subpass.depthStencilResolve > colorCount) 
            {
                subpass.depthStencilResolve = colorCount;
            }
        }
    }

    cmdFuncCreateRenderPass(ll::glDevice::GetInstance(), _gpuRenderPass);
}

void ll::glRenderPass::DoDestroy()
{
}
