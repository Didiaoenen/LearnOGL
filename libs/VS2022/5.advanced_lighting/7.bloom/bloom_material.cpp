#include "bloom_material.h"

bloom_material::bloom_material()
{
}

bloom_material::bloom_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

bloom_material::~bloom_material()
{
}

void bloom_material::Draw()
{
	mShader->Use();
	
	if (mDiffuseTex)
	{
		mDiffuseTex->Bind(GL_TEXTURE0);
	}
}
