#pragma once

#include "LearnOGLShader.h"
#include "LearnOGLTexture.h"

class LearnOGLMaterial
{
public:
	LearnOGLMaterial();
	~LearnOGLMaterial();

public:

	LearnOGLShader mShader;

	LearnOGLTexture mDiffuseTexture;

	LearnOGLTexture mNormalTexture;

private:
};

