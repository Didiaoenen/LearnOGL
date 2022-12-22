#include "point_shadow_material.h"

point_shadow_material::point_shadow_material() :
	mDiffuseTex(nullptr),
	mDepthAttribID(0)
{
}

point_shadow_material::point_shadow_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader),
	mDiffuseTex(nullptr),
	mDepthAttribID(0)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mDepthAttribID = mShader->GetUniformLocation(mDepthMapLoc);
}

point_shadow_material::~point_shadow_material()
{
}

void point_shadow_material::Draw()
{
	mShader->Use();

	if (mDiffuseTex)
	{
		mDiffuseTex->Bind();
	}
}
