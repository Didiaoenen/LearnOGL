#include "ssao_blur_material.h"

ssao_blur_material::ssao_blur_material()
{
}

ssao_blur_material::ssao_blur_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mSSAOLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

ssao_blur_material::~ssao_blur_material()
{
	mShader->Use();

}
