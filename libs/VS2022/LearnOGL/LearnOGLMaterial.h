#pragma once

#include "LearnOGLShader.h"
#include "LearnOGLTexture.h"

#include <string>

namespace OGL
{
	class LearnOGLMaterial
	{
	public:
		LearnOGLMaterial();
		LearnOGLMaterial(LearnOGLShader* oglShader);
		~LearnOGLMaterial();

		void Draw();

	public:

		LearnOGLShader* mShader;

		LearnOGLTexture* mDiffuseTexture;

		LearnOGLTexture* mNormalTexture;

		LearnOGLTexture* mRoughnessTexture;
	
		LearnOGLTexture* mSpecularTexture;

	private:
		std::string oglDiffuseLoc = "diffuseTex";
		std::string oglNormalLoc = "normalTex";
		std::string oglRoughnessLoc = "roughnessTex";
		std::string oglSpecularLoc = "specularTex";
	};
}