#include "parallax_material.h"

parallax_material::parallax_material()
{
}

parallax_material::parallax_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mNormalTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
	mShader->SetTexUnit(mDepthMapLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x02);
}

parallax_material::~parallax_material()
{
}

void parallax_material::Draw()
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

	if (mDepthTex)
	{
		mDepthTex->Bind(GL_TEXTURE2);
	}
}
