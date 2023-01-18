#include "LearnOGLTexture.h"

namespace OGL
{
	LearnOGLTexture::LearnOGLTexture(const std::string path, bool flip/* = false*/, bool gammaCorrection/* = false*/, TextureType textureType/* = TextureType::Diffuse*/, GLenum targetType/* = GL_TEXTURE_2D*/) :
		mPath(path), mTextureType(textureType), mTargetType(targetType)
	{
		stbi_set_flip_vertically_on_load(flip);

		auto imageData = stbi_load(path.c_str(), &imageWidth, &imageHeight, &imageChannels, 0);
		if (!imageData)
		{
			std::cout << "Error::Texture load failed: " << path << std::endl;
			stbi_image_free(imageData);
			return;
		}

		GLenum format;
		GLenum dataFormat;
		switch (imageChannels)
		{
		case 1:
			format = dataFormat = GL_RED;
			break;

		case 3:
			format = gammaCorrection ? GL_SRGB : GL_RGB;
			dataFormat = GL_RGB;
			break;

		case 4:
			format = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
			dataFormat = GL_RGBA;
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
				glTexImage2D(targetType, 0, format, imageWidth, imageHeight, 0, dataFormat, GL_UNSIGNED_BYTE, imageData);
			}
				break;

			default:
				break;
			}

			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(targetType, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(targetType, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(targetType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(targetType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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