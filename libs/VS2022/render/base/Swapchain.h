#pragma once

#include "Ptr.h"
#include "Def_common.h"

namespace ll
{

class Swapchain
{
public:
	Swapchain();
	virtual ~Swapchain();

	void Initialize(const SwapchainInfo& info);

	inline void* GetWindowHandle() const { return _windowHandle; }
	inline VsyncMode GetVSyncMode() const { return _vsyncMode; }

	inline Texture* GetColorTexture() const { return _colorTexture; }
	inline Texture* GetDepthStencilTexture() const { return _depthStencilTexture; }

	inline SurfaceTransform GetSurfaceTransform() const { return _transform; }
	inline uint32_t GetWidth() const { return _colorTexture->GetWidth(); }
	inline uint32_t GetHeight() const { return _colorTexture->GetHeight(); }

protected:
	virtual void DoInit(const SwapchainInfo& info) = 0;
	virtual void DoDestroy() = 0;
	virtual void DoDestroySurface() = 0;
	virtual void DoCreateSurface(void* windowHandle) = 0;

	static inline void InitTexture(const SwapchainTextureInfo& info, Texture* texture) 
	{
		Texture::Initialize(info, texture);
	}

	void* _windowHandle{ nullptr };
	VsyncMode _vsyncMode{ VsyncMode::RELAXED };
	SurfaceTransform _transform{ SurfaceTransform::IDENTITY };
	bool _preRotationEnabled{ false };

	IntrusivePtr<Texture> _colorTexture;
	IntrusivePtr<Texture> _depthStencilTexture;
};

}
