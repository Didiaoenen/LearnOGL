#pragma once

#include <string>
#include <iostream>

#include "Image.h"

#include "OGL_Base.h"
#include "OGL_Asset.h"

namespace OGL
{
class OGL_Texture : public OGL_Asset
{
public:
	OGL_Texture() = default;
	OGL_Texture(const std::string& name) : mName(name) {}
	virtual ~OGL_Texture() = default;

	bool LoadTexture();
	Ref<Image> GetTextureImage();

public:
	std::string mName{ std::string() };
	std::string mPath{ std::string() };

	void* mData{ nullptr };

	int mWidth{ 0 };
	int mHeight{ 0 };
	int mChannels{ 0 };

	Ref<Image> mImage{};

	bool mHDR{ false };
	bool mFlip{ false };
	bool mGammaCorrection{ false };

	bool mLoaded{ false };
};
}