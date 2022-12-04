#pragma once

#include "LearnOGLShader.h"
#include "LearnOGLTexture.h"

namespace OGL
{
	class LearnOGLMaterial
	{
	public:
		LearnOGLMaterial();
		~LearnOGLMaterial();

	public:

		LearnOGLShader* mShader;

		LearnOGLTexture* mDiffuseTexture;

		LearnOGLTexture* mNormalTexture;

		LearnOGLTexture* mRoughnessTexture;
	
		LearnOGLTexture* mSpecularTexture;

	private:
	};
}

