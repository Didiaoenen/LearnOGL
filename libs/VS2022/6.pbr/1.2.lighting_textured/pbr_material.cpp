#include "pbr_material.h"

pbr_material::pbr_material()
{
}

pbr_material::pbr_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mAlbedoLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mNormalLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
	mShader->SetTexUnit(mMetallicLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x02);
	mShader->SetTexUnit(mRoughnessLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x03);
	mShader->SetTexUnit(mAOLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x04);
}

pbr_material::~pbr_material()
{
}

void pbr_material::Draw()
{
	mShader->Use();

	if (mAlbedoTex)
	{
		mAlbedoTex->Bind(GL_TEXTURE0);
	}

	if (mNormalTex)
	{
		mNormalTex->Bind(GL_TEXTURE1);
	}

	if (mMetallicTex)
	{
		mMetallicTex->Bind(GL_TEXTURE2);
	}

	if (mRoughnessTex)
	{
		mRoughnessTex->Bind(GL_TEXTURE3);
	}

	if (mAOTex)
	{
		mAOTex->Bind(GL_TEXTURE4);
	}
}
