#include "LearnOGLTexture.h"

namespace OGL
{
	LearnOGLTexture::LearnOGLTexture(const std::string path, TextureType textureType/* = TextureType::Diffuse*/, GLenum targetType/* = GL_TEXTURE_2D*/)
		: mID(0), mPath(path), mTextureType(textureType), mTargetType(targetType)
	{
		auto imageData = stbi_load(path.c_str(), &imageWidth, &imageHeight, &imageChannels, 0);
		if (!imageData)
		{
			std::cout << "Error::Texture load failed" << path << std::endl;
			stbi_image_free(imageData);
			return;
		}
		GLenum format = 0;
		switch (imageChannels)
		{
		case 1:
			format = GL_RED;
			break;

		case 3:
			format = GL_RGB;
			break;

		case 4:
			format = GL_RGBA;
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
				glTexImage2D(targetType, 0, format, imageWidth, imageHeight, 0, format, GL_UNSIGNED_BYTE, imageData);
			}
				break;

			default:
				break;
			}

			glTexParameteri(targetType, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(targetType, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(targetType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(targetType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		glBindTexture(targetType, 0);

		stbi_image_free(imageData);
	}

	LearnOGLTexture::~LearnOGLTexture()
	{
	}

	void LearnOGLTexture::Bind(GLenum textureUnit/* = GL_TEXTURE0*/)
	{
		glActiveTexture(textureUnit);
		glBindTexture(mTargetType, mID);
	}
}