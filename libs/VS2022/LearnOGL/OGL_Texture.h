#pragma once

#include <string>

#include <stb_image.h>

namespace OGL
{
class OGL_Texture
{
public:
	OGL_Texture(const std::string& path);
	~OGL_Texture() = default;

public:
	std::string mPath{ "" };

	void* mData{ nullptr };

	int mWidth{ 0 };
	int mHeight{ 0 };
	int mChannels{ 0 };

};
}