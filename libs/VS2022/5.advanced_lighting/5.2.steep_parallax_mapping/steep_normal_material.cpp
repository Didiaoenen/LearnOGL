#include "steep_normal_material.h"

steep_normal_material::steep_normal_material()
{
}

steep_normal_material::steep_normal_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mNormalTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
}

steep_normal_material::~steep_normal_material()
{
}

void steep_normal_material::Draw()
{
	mShader->Use();

	if (mDiffuseTex)
	{
		mDiffuseTex->Bind(GL_TEXTURE0);
	}

	if (mNormalTex)
	{
		mNormalTex->Bind(GL_TEXTURE1);
	}
}