#pragma once

#include "Def_common.h"

namespace ll
{

class RenderPass
{
public:
    RenderPass();
    virtual ~RenderPass();

    void Initialize(const RenderPassInfo& info);
    void Destroy();

    inline const ColorAttachmentList& GetColorAttachments() const { return _colorAttachments; }
    inline const DepthStencilAttachment& GetDepthStencilAttachment() const { return _depthStencilAttachment; }
    inline const SubpassInfoList& GetSubpasses() const { return _subpasses; }
    inline const SubpassDependencyList& GetDependencies() const { return _dependencies; }

protected:
    virtual void DoInit(const RenderPassInfo& info) = 0;
    virtual void DoDestroy() = 0;

    ColorAttachmentList _colorAttachments;
    DepthStencilAttachment _depthStencilAttachment;
    SubpassInfoList _subpasses;
    SubpassDependencyList _dependencies;
};

}