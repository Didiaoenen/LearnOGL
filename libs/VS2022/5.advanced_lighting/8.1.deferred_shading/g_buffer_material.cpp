#include "g_buffer_material.h"

g_buffer_material::g_buffer_material()
{
}

g_buffer_material::g_buffer_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mSpecularLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
}

g_buffer_material::~g_buffer_material()
{
}

void g_buffer_material::Draw()
{
	mShader->Use();

	if (mDiffuseTex)
	{
		mDiffuseTex->Bind(GL_TEXTURE0);
	}

	if (mSpecularTex)
	{
		mSpecularTex->Bind(GL_TEXTURE1);
	}
}
