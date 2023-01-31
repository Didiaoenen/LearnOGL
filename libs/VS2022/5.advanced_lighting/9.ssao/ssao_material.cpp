#include "ssao_material.h"

ssao_material::ssao_material()
{
}

ssao_material::ssao_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mPosLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mNormalLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
	mShader->SetTexUnit(mTexNoiseLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x02);
}

ssao_material::~ssao_material()
{
}

void ssao_material::Draw()
{
	mShader->Use();
}
