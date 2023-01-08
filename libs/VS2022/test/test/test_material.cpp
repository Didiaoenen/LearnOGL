#include "test_material.h"

test_material::test_material()
{
}

test_material::test_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

test_material::~test_material()
{
}

void test_material::Draw()
{
	mShader->Use();

	if (mDiffuseTexture)
	{
		mDiffuseTexture->Bind(GL_TEXTURE0);
	}
}
