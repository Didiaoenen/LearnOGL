#include "pbr_material.h"

pbr_material::pbr_material()
{
}

pbr_material::pbr_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mIrradianceLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

pbr_material::~pbr_material()
{
}

void pbr_material::Draw()
{
	mShader->Use();

	if (mIrradianceTex)
	{
		mIrradianceTex->Bind(GL_TEXTURE0);
	}
}
