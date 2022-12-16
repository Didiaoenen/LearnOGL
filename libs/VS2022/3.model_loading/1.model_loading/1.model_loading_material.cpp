#include "1.model_loading_material.h"

model_loading_material::model_loading_material() :
	mDiffuseTexture(nullptr),
	mNormalTexture(nullptr),
	mRoughnessTexture(nullptr),
	mSpecularTexture(nullptr)
{
}

model_loading_material::model_loading_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader),
	mDiffuseTexture(nullptr),
	mNormalTexture(nullptr),
	mRoughnessTexture(nullptr),
	mSpecularTexture(nullptr)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mNormalLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
	mShader->SetTexUnit(mRoughnessLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x02);
	mShader->SetTexUnit(mSpecularLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x03);
}

model_loading_material::~model_loading_material()
{
}

void model_loading_material::Draw()
{
	mShader->Use();

	if (mDiffuseTexture)
	{
		mDiffuseTexture->Bind(GL_TEXTURE0);
	}

	if (mNormalTexture)
	{
		mNormalTexture->Bind(GL_TEXTURE1);
	}

	if (mRoughnessTexture)
	{
		mRoughnessTexture->Bind(GL_TEXTURE2);
	}

	if (mSpecularTexture)
	{
		mSpecularTexture->Bind(GL_TEXTURE3);
	}
}