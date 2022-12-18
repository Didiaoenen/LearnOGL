#include "debug_shadow_material.h"

debug_shadow_material::debug_shadow_material() :
	mDepthAttribID(0)
{
}

debug_shadow_material::debug_shadow_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader),
	mDepthAttribID(0)

{
	mShader->Use();
	mShader->SetTexUnit(mDepthMapLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);

	mDepthAttribID = mShader->GetUniformLocation(mDepthMapLoc);
}

debug_shadow_material::~debug_shadow_material()
{
}

void debug_shadow_material::Draw()
{
	mShader->Use();

	if (mCommand->mUintTexMap.find(mDepthAttribID) != mCommand->mUintTexMap.end())
	{
		mCommand->mUintTexMap.find(mDepthAttribID)->second->BindForReading();
	}
}
