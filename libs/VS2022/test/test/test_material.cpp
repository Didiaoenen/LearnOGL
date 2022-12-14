#include "test_material.h"

test_material::test_material() :
	mDiffuseTexture(nullptr)
{
}

test_material::test_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader),
	mDiffuseTexture(nullptr)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseLoc, (uint32_t)OGL::TexCoord::TexCoord0x00);
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
