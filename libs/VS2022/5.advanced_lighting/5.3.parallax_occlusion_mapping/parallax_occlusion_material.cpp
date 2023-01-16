#include "parallax_occlusion_material.h"

parallax_occlusion_material::parallax_occlusion_material()
{
}

parallax_occlusion_material::parallax_occlusion_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mNormalTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
	mShader->SetTexUnit(mDepthTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x02);
}

parallax_occlusion_material::~parallax_occlusion_material()
{
}

void parallax_occlusion_material::Draw()
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
