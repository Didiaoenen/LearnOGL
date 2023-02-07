#include "LearnOGLTexture.h"

namespace OGL
{
	LearnOGLTexture::LearnOGLTexture(GLuint width, GLuint height, const void* pixels, TextureType textureType, GLenum targetType) :
		mTextureType(textureType), mTargetType(targetType)
	{
		glGenTextures(1, &mID);
		glBindTexture(GL_TEXTURE_2D, mID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGB, GL_FLOAT, pixels);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	LearnOGLTexture::LearnOGLTexture(const std::string path, bool flip/* = false*/, bool gammaCorrection/* = false*/, bool mipmap/* = false*/, bool hdr/* = false*/, TextureType textureType/* = TextureType::Diffuse*/, GLenum targetType/* = GL_TEXTURE_2D*/) :
		mPath(path), mTextureType(textureType), mTargetType(targetType)
	{
		stbi_set_flip_vertically_on_load(flip);

		void* imageData;
		if (hdr)
		{
			imageData = (void*)stbi_loadf(path.c_str(), &imageWidth, &imageHeight, &imageChannels, 0);
		}
		else
		{
			imageData = (void*)stbi_load(path.c_str(), &imageWidth, &imageHeight, &imageChannels, 0);
		}

		if (!imageData)
		{
			std::cout << "Error::Texture load failed: " << path << std::endl;
			stbi_image_free(imageData);
			return;
		}

		GLenum format;
		GLenum dataFormat;
		GLenum dataType;
		switch (imageChannels)
		{
		case 1:
			format = dataFormat = GL_RED;
			dataType = GL_UNSIGNED_BYTE;
			break;

		case 3:
			format = hdr ? GL_RGB16F : (gammaCorrection ? GL_SRGB : GL_RGB);
			dataFormat = GL_RGB;
			dataType = GL_FLOAT;
			break;

		case 4:
			format = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
			dataFormat = GL_RGBA;
			dataType = GL_UNSIGNED_BYTE;
			break;

		default:
			break;
		}

		glGenTextures(1, &mID);
		glBindTexture(targetType, mID);
		{
			switch (targetType)
			{
			case GL_TEXTURE_2D:
			{
				glTexImage2D(targetType, 0, format, imageWidth, imageHeight, 0, dataFormat, dataType, imageData);
			}
				break;

			default:
				break;
			}

			GLuint minFilter = GL_LINEAR;
			GLuint magFilter = GL_LINEAR;
			if (mipmap)
			{
				glGenerateMipmap(GL_TEXTURE_2D);
				minFilter = GL_LINEAR_MIPMAP_LINEAR;
				magFilter = GL_LINEAR_MIPMAP_LINEAR;
			}

			glTexParameteri(targetType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(targetType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(targetType, GL_TEXTURE_MIN_FILTER, minFilter);
			glTexParameteri(targetType, GL_TEXTURE_MAG_FILTER, magFilter);
		}
		glBindTexture(targetType, 0);

		stbi_image_free(imageData);
	}

	LearnOGLTexture::~LearnOGLTexture()
	{
		std::cout << "LearnOGLTexture::~LearnOGLTexture" << std::endl;
	}

	void LearnOGLTexture::Bind(GLenum textureUnit/* = GL_TEXTURE0*/)
	{
		glActiveTexture(textureUnit);
		glBindTexture(mTargetType, mID);
	}
}