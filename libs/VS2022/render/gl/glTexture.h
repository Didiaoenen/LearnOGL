#pragma once

#include "../base/Texture.h"

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