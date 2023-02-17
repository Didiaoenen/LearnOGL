#include "Texture.h"

ll::Texture::Texture()
{
}

ll::Texture::~Texture() = default;

void ll::Texture::Initialize(const TextureInfo& info)
{
	_info = info;

	_viewInfo.texture = this;
	_viewInfo.format = _info.format;
	_viewInfo.type = _info.type;
	_viewInfo.baseLayer = 0;
	_viewInfo.layerCount = _info.layerCount;
	_viewInfo.baseLayer = 0;
	_viewInfo.levelCount = _info.levelCount;

	DoInit(info);
}

void ll::Texture::Initialize(const TextureViewInfo& info)
{
	_info = info.texture->GetInfo();
	_viewInfo = info;

	_isTextureView = true;

	DoInit(info);
}

void ll::Texture::Destroy()
{
	DoDestroy();

	_info = TextureInfo();
	_viewInfo = TextureViewInfo();

	_isTextureView = false;
}

void ll::Texture::Initialize(const SwapchainTextureInfo& info, Texture* out)
{
    out->_info.type = TextureType::TEX2D;
    out->_info.format = info.format;
    out->_info.width = info.width;
    out->_info.height = info.height;
    out->_info.layerCount = 1;
    out->_info.levelCount = 1;
    out->_info.depth = 1;
    out->_info.samples = SampleCount::ONE;
    out->_info.flags = TextureFlagBit::NONE;
    out->_info.usage = GFX_FORMAT_INFOS[toNumber(info.format)].hasDepth
        ? TextureUsageBit::DEPTH_STENCIL_ATTACHMENT
        : TextureUsageBit::COLOR_ATTACHMENT;

    out->_swapchain = info.swapchain;

    out->_viewInfo.texture = out;
    out->_viewInfo.format = out->_info.format;
    out->_viewInfo.type = out->_info.type;
    out->_viewInfo.baseLayer = 0;
    out->_viewInfo.layerCount = out->_info.layerCount;
    out->_viewInfo.baseLevel = 0;
    out->_viewInfo.levelCount = out->_info.levelCount;

    out->DoInit(info);
}