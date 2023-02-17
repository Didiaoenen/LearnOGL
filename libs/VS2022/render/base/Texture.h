#pragma once

#include "Def.h"
#include "Def_common.h"

namespace ll
{

class Texture
{
public:
	Texture();
	virtual ~Texture();

	void Initialize(const TextureInfo& info);
	void Initialize(const TextureViewInfo& info);
	void Destroy();

	inline const TextureInfo& GetInfo() const { return _info; }
	inline const TextureViewInfo& GetViewInfo() const { return _viewInfo; }

	inline bool IsTextureView() const { return _isTextureView; }

	inline Format GetFormat() const { return _info.format; }
	inline uint32_t GetWidth() const { return _info.width; }
	inline uint32_t GetHeight() const { return _info.height; }

	virtual const Texture* getRaw() const { return this; }

protected:
	friend class Swapchain;

	virtual void DoInit(const TextureInfo& info) = 0;
	virtual void DoInit(const TextureViewInfo& info) = 0;
	virtual void DoDestroy() = 0;

	virtual void DoInit(const SwapchainTextureInfo& info) = 0;

	static void Initialize(const SwapchainTextureInfo& info, Texture* out);

	TextureInfo _info;
	TextureViewInfo _viewInfo;

	Swapchain* _swapchain{ nullptr };
	bool _isTextureView{ false };
};

}

