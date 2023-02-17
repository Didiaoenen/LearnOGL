#pragma once

#include "Def.h"
#include "glDevice.h"
#include "glObjects.h"
#include "glCommands.h"

#include "Texture.h"
#include "glSwapchain.h"

namespace ll
{

struct GPUTexture;

class glTexture final : public Texture
{
public:
	glTexture();
	~glTexture() override;

	inline GPUTexture* GpuTexture() const { return _gpuTexture; }

protected:
	void DoInit(const TextureInfo &info) override;
	void DoInit(const TextureViewInfo &info) override;
	void DoInit(const SwapchainTextureInfo &info) override;

	void DoDestroy() override;

	GPUTexture* _gpuTexture{ nullptr };
};

}