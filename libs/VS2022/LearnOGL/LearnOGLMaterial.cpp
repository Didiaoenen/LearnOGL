#include "LearnOGLMaterial.h"

namespace OGL
{
	LearnOGLMaterial::LearnOGLMaterial()
		:mShader(nullptr), mDiffuseTexture(nullptr), mNormalTexture(nullptr), mRoughnessTexture(nullptr), mSpecularTexture(nullptr)
	{
	}

	LearnOGLMaterial::LearnOGLMaterial(LearnOGLShader* oglShader)
		:mShader(oglShader), mDiffuseTexture(nullptr), mNormalTexture(nullptr), mRoughnessTexture(nullptr), mSpecularTexture(nullptr)
	{
		mShader->Use();
		mShader->SetTexUnit(oglDiffuseLoc, 0);
		mShader->SetTexUnit(oglNormalLoc, 1);
		mShader->SetTexUnit(oglRoughnessLoc, 2);
		mShader->SetTexUnit(oglSpecularLoc, 3);
	}

	LearnOGLMaterial::~LearnOGLMaterial()
	{
		delete mShader;
		delete mDiffuseTexture;
		delete mNormalTexture;
		delete mRoughnessTexture;
		delete mSpecularTexture;
	}
	
	void LearnOGLMaterial::Draw()
	{
		mDiffuseTexture->Bind(GL_TEXTURE0);
		mNormalTexture->Bind(GL_TEXTURE1);
		mRoughnessTexture->Bind(GL_TEXTURE2);
		mSpecularTexture->Bind(GL_TEXTURE3);
	}
}
