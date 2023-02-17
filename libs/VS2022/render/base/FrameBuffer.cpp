#include "FrameBuffer.h"

ll::FrameBuffer::FrameBuffer()
{
}

ll::FrameBuffer::~FrameBuffer()
{
}

void ll::FrameBuffer::Initialize(const FramebufferInfo& info)
{
    _renderPass = info.renderPass;
    _colorTextures = info.colorTextures;
    _depthStencilTexture = info.depthStencilTexture;

    DoInit(info);
}

void ll::FrameBuffer::Destroy()
{
}
