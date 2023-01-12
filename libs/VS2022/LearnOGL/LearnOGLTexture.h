#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include <string>
#include <iostream>

namespace OGL
{
	enum class TextureType
	{
		None = 0,
		Diffuse,
		Normal,
		Parallax,
		Roughness,
		Specular,
	};

	class LearnOGLTexture
	{
	public:
		LearnOGLTexture(const std::string path, bool flip = false, TextureType textureType = TextureType::Diffuse, GLenum targetType = GL_TEXTURE_2D);
		~LearnOGLTexture();

		void Bind(GLenum textureUnit = GL_TEXTURE0);
		

	public:
		GLuint mID{ 0 };
		std::string mPath;
		GLenum mTargetType;
		TextureType mTextureType;

		int imageWidth;
		int imageHeight;
		int imageChannels;
	private:
	};
}

