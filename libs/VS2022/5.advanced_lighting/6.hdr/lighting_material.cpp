#include "lighting_material.h"

lighting_material::lighting_material()
{
}

lighting_material::lighting_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

lighting_material::~lighting_material()
{
}

void lighting_material::Draw()
{
	mShader->Use();
	
	if (mDiffuseTex)
	{
		mDiffuseTex->Bind(GL_TEXTURE0);
	}
}
