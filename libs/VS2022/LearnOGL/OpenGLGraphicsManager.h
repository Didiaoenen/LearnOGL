#pragma once

#include "OpenGLGraphicsCommonBaseManager.h"

namespace OGL
{
class OpenGLGraphicsManager : public OpenGLGraphicsCommonBaseManager
{
public:
	bool Initialize() final;
	void Finalize() final;

	void CreateTextureView(Texture2D& textureView, const TextureArrayBase& textureArray, const uint32_t slice, const uint32_t mip) final;

	void BeginPass(Frame& frame) final;
	void EndPass(Frame& frame) final;

private:
	void GetOpenGLTextureFormat(const PixelFormat pixelFormat, uint32_t& format, uint32_t& internalFormat, uint32_t& type) final;

	void GetOpenGLTextureFormat(const CompressedFormat compressedFormat, uint32_t& format, uint32_t& internalFormat, uint32_t& type) final;

private:

	void BeginFrame(Frame& frame);
	void EndFrame(Frame& frame);
};
}

