#include "glTexture.h"

ll::glTexture::glTexture()
{
}

ll::glTexture::~glTexture()
{
}

void ll::glTexture::DoInit(const TextureInfo& /*info*/)
{
    _gpuTexture = new GPUTexture;
    _gpuTexture->type = _info.type;
    _gpuTexture->format = _info.format;
    _gpuTexture->usage = _info.usage;
    _gpuTexture->width = _info.width;
    _gpuTexture->height = _info.height;
    _gpuTexture->depth = _info.depth;
    _gpuTexture->arrayLayer = _info.layerCount;
    _gpuTexture->mipLevel = _info.levelCount;
    _gpuTexture->samples = _info.samples;
    _gpuTexture->flags = _info.flags;
    _gpuTexture->glTexture = static_cast<GLuint>(reinterpret_cast<size_t>(_info.externalRes));

    cmdFuncCreateTexture(glDevice::GetInstance(), _gpuTexture);

}

void ll::glTexture::DoInit(const TextureViewInfo& info)
{
    _gpuTexture = static_cast<glTexture*>(info.texture)->GpuTexture();
}

void ll::glTexture::DoInit(const SwapchainTextureInfo& /*info*/)
{
    _gpuTexture = new GPUTexture;
    _gpuTexture->type = _info.type;
    _gpuTexture->format = _info.format;
    _gpuTexture->usage = _info.usage;
    _gpuTexture->width = _info.width;
    _gpuTexture->height = _info.height;
    _gpuTexture->depth = _info.depth;
    _gpuTexture->arrayLayer = _info.layerCount;
    _gpuTexture->mipLevel = _info.levelCount;
    _gpuTexture->samples = _info.samples;
    _gpuTexture->flags = _info.flags;
    _gpuTexture->swapchain = static_cast<glSwapchain*>(_swapchain)->GpuSwapchain();
}

void ll::glTexture::DoDestroy()
{

}