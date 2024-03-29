#include "OGL_Texture.h"

#include <stb_image.h>

using namespace OGL;

bool OGL_Texture::LoadTexture()
{
	if (mLoaded)
	{
		return true;
	}

	stbi_set_flip_vertically_on_load(mFlip);

	mImage = CreateRef<Image>();

	int channels;
	void* imageData = (void*)stbi_load(("./../../../resources/objects/" + mName).c_str(), &mImage->width, &mImage->height, &channels, 0);

	if (!imageData)
	{
		std::cout << "Error::Texture load failed: " << mName << std::endl;
		stbi_image_free(imageData);
		return false;
	}

	GLenum internalFormat = 0, dataFormat = 0, dataType = 0;
	switch (channels)
	{
	case 1:
		mImage->pixelFormat = PixelFormat::R8;
		mImage->imageDataType = ImageDataType::UNSIGNED_BYTE;
		mImage->imageDataFormat = ImageDataFormat::RED;

		break;

	case 3:
		mImage->pixelFormat = PixelFormat::RGB8;
		mImage->imageDataType = ImageDataType::UNSIGNED_BYTE;
		mImage->imageDataFormat = ImageDataFormat::RGB;
		break;

	case 4:
		mImage->pixelFormat = PixelFormat::RGBA8;
		mImage->imageDataType = ImageDataType::UNSIGNED_BYTE;
		mImage->imageDataFormat = ImageDataFormat::RGBA;
		break;

	default:
		break;
	}

	mImage->data = imageData;

	mLoaded = true;

	return true;
}

Ref<Image> OGL_Texture::GetTextureImage()
{
	if (LoadTexture())
	{
		return mImage;
	}
	return nullptr;
}