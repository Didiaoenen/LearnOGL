#include "blur_material.h"

blur_material::blur_material()
{
}

blur_material::blur_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mImageTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

blur_material::~blur_material()
{
}

void blur_material::Draw()
{
	mShader->Use();

	if (mImageTex)
	{
		mImageTex->Bind(GL_TEXTURE0);
	}
}
