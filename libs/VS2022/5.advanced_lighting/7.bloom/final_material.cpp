#include "final_material.h"

final_material::final_material()
{
}

final_material::final_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mSceneTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mBloomBlurTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
	mSceneTexAttribID = mShader->GetUniformLocation(mSceneTexLoc);
}

final_material::~final_material()
{
}

void final_material::Draw()
{
	mShader->Use();

	if (mCommand->mUintTexMap.find(mSceneTexAttribID) != mCommand->mUintTexMap.end())
	{
		mCommand->mUintTexMap.find(mSceneTexAttribID)->second->BindForReading(GL_TEXTURE0, 0);
	}
}
