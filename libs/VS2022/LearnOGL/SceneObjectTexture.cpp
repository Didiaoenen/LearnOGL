#include "SceneObjectTexture.h"

#include <iostream>

#include <stb_image.h>

using namespace OGL;
using namespace std;

bool SceneObjectTexture::LoadTexture()
{
	if (mLoaded)
	{
		return true;
	}

	stbi_set_flip_vertically_on_load(mFlip);

	int channels;
	void* imageData = (void*)stbi_load(mName.c_str(), &mImage->width, &mImage->height, &channels, 0);

	if (!imageData)
	{
		cout << "Error::Texture load failed: " << mName << endl;
		stbi_image_free(imageData);
		return false;
	}

	GLenum internalFormat = 0, dataFormat = 0, dataType = 0;
	switch (channels)
	{
	case 1:
		//internalFormat = GL_R8;
		//dataFormat = GL_RED;
		//dataType = GL_UNSIGNED_BYTE;
		mImage->pixelFormat = PixelFormat::R8;
		mImage->imageDataType = ImageDataType::UNSIGNED_BYTE;
		mImage->imageDataFormat = ImageDataFormat::RED;

		break;

	case 3:
		//internalFormat = GL_RGB8;
		//dataFormat = GL_RGB;
		//dataType = GL_UNSIGNED_BYTE;
		mImage->pixelFormat = PixelFormat::RGB8;
		mImage->imageDataType = ImageDataType::UNSIGNED_BYTE;
		mImage->imageDataFormat = ImageDataFormat::RGB;
		break;

	case 4:
		//internalFormat = GL_RGBA8;
		//dataFormat = GL_RGBA;
		//dataType = GL_UNSIGNED_BYTE;
		mImage->pixelFormat = PixelFormat::RGBA8;
		mImage->imageDataType = ImageDataType::UNSIGNED_BYTE;
		mImage->imageDataFormat = ImageDataFormat::RGBA;
		break;

	default:
		break;
	}

	mImage->data = imageData;
	stbi_image_free(imageData);

	mLoaded = true;

	return mLoaded;
}

shared_ptr<Image> OGL::SceneObjectTexture::GetTextureImage()
{
	if (LoadTexture())
	{
		return mImage;
	}
	return nullptr;
}
