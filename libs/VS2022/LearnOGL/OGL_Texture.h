#pragma once

#include <string>

#include "OGL_Asset.h"

namespace OGL
{
class OGL_Texture : public OGL_Asset
{
public:
	OGL_Texture() = default;
	OGL_Texture(const std::string& name) : mName(name) {}
	virtual ~OGL_Texture() = default;

public:
	std::string mName{ std::string() };
	std::string mPath{ std::string() };

	void* mData{ nullptr };

	int mWidth{ 0 };
	int mHeight{ 0 };
	int mChannels{ 0 };
};
}