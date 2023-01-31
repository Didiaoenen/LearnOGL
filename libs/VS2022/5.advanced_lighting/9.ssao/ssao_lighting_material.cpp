#include "ssao_lighting_material.h"

ssao_lighting_material::ssao_lighting_material()
{
}

ssao_lighting_material::ssao_lighting_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mPosLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mNormalLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
	mShader->SetTexUnit(mAlbedoLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x02);
	mShader->SetTexUnit(mSSAOLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x03);
}

ssao_lighting_material::~ssao_lighting_material()
{
}

void ssao_lighting_material::Draw()
{
	mShader->Use();
}
