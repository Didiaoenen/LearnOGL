#include "cubemap_material.h"

cubemap_material::cubemap_material()
{
}

cubemap_material::cubemap_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mEquirectangularLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

cubemap_material::~cubemap_material()
{
}

void cubemap_material::Draw()
{
	mShader->Use();

	if (mEquirectangularTex)
	{
		mEquirectangularTex->Bind(GL_TEXTURE0);
	}
}

void cubemap_material::SetTexture(OGL::LearnOGLTexture* texture)
{
	bool bContains = false;
	for (auto& tex : mTexVec)
	{
		if (tex == texture)
		{
			bContains = true;
		}
	}
	if (!bContains)
	{
		mTexVec.push_back(texture);
	}
}

void cubemap_material::BindTextures(uint32_t count)
{
	for (auto& tex : mTexVec)
	{
		tex->Bind(GL_TEXTURE0 + count);
		count++;
	}
}
