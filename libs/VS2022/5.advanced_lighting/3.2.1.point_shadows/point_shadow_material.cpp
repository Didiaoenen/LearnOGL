#include "point_shadow_material.h"

point_shadow_material::point_shadow_material()
{
}

point_shadow_material::point_shadow_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mDepthMapLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);

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
		mDiffuseTex->Bind(GL_TEXTURE0);
	}

	if (mCommand->mUintTexMap.find(mDepthAttribID) != mCommand->mUintTexMap.end())
	{
		mCommand->mUintTexMap.find(mDepthAttribID)->second->BindForReading(GL_TEXTURE1);
	}
}
