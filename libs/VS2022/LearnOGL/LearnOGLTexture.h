#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include "LearnOGLModel.h"

#include <string>
#include <iostream>

namespace OGL
{
	class LearnOGLTexture
	{
	public:
		LearnOGLTexture(const std::string path, TextureType textureType = TextureType::Diffuse, GLenum targetType = GL_TEXTURE_2D);
		~LearnOGLTexture();

		void Bind(GLenum textureUnit = GL_TEXTURE0);

	public:
		GLuint mID;
		std::string mPath;
		GLenum mTargetType;
		TextureType mTextureType;

		int imageWidth;
		int imageHeight;
		int imageChannels;
	private:
	};
}

