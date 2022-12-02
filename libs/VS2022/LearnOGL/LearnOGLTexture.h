#pragma once

#include <glad/glad.h>
#include <stb_image.h>

#include "LearnOGLModel.h"

#include <string>
#include <iostream>

class LearnOGLTexture
{
public:
	LearnOGLTexture(const std::string path, LearnOGLModel::TextureType textureType = LearnOGLModel::TextureType::Diffuse, GLenum targetType = GL_TEXTURE_2D);
	~LearnOGLTexture();

	void Bind(GLenum textureUnit/* = GL_TEXTURE0*/);

public:
	UINT mID;
	std::string mPath;
	GLenum mTargetType;
	LearnOGLModel::TextureType mTextureType;

	int imageWidth;
	int imageHeight;
	int imageChannels;
private:
};

