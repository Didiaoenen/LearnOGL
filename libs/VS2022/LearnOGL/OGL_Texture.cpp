#include "OGL_Texture.h"

using namespace OGL;

OGL_Texture::OGL_Texture(const std::string& path)
	: mPath(path)
{
	stbi_set_flip_vertically_on_load(true);

	std::string ext = mPath.substr(mPath.find_last_of('.'));

	if (ext.compare(".hdr"))
	{
		mData = stbi_loadf(mPath.c_str(), &mWidth, &mHeight, &mChannels, 0);
	}
	else
	{
		mData = stbi_load(mPath.c_str(), &mWidth, &mHeight, &mChannels, 0);
	}
}
