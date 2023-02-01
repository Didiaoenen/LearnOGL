#include "shadow_material.h"

shadow_material::shadow_material()
{
}

shadow_material::shadow_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mDiffuseTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mShadowMapLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);

	mDepthAttribID = mShader->GetAttribID(mShadowMapLoc);
}

shadow_material::~shadow_material()
{
}

void shadow_material::Draw()
{
	mShader->Use();

	if (mDiffuseTex)
	{
		mDiffuseTex->Bind(GL_TEXTURE0);
	}

	if (mCommand->mUnitTexMap.find(mDepthAttribID) != mCommand->mUnitTexMap.end())
	{
		mCommand->mUnitTexMap.find(mDepthAttribID)->second->BindForReading(GL_TEXTURE1);
	}
}