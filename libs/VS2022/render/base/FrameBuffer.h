#pragma once

#include "Def_common.h"

namespace ll
{

class RenderPass;

class FrameBuffer
{
public:
	FrameBuffer();
	virtual ~FrameBuffer();


    void Initialize(const FramebufferInfo& info);
    void Destroy();

    inline RenderPass* GetRenderPass() const { return _renderPass; }
    inline const TextureList& GetColorTextures() const { return _colorTextures; }
    inline Texture* GetDepthStencilTexture() const { return _depthStencilTexture; }

protected:
    virtual void DoInit(const FramebufferInfo& info) = 0;
    virtual void DoDestroy() = 0;

    RenderPass* _renderPass{ nullptr };
    TextureList _colorTextures;
    Texture* _depthStencilTexture{ nullptr };
};

}