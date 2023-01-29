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
	mSceneTexAttribID = mShader->GetAttribID(mSceneTexLoc);
}

final_material::~final_material()
{
}

void final_material::Draw()
{
	mShader->Use();

	auto unitTex = mCommand->mUnitTexMap.find(mSceneTexAttribID);
	if (unitTex != mCommand->mUnitTexMap.end())
	{
		unitTex->second->BindForReading(GL_TEXTURE0, 0);
	}

	unitTex = mCommand->mUnitTexMap.find(mAttribID);
	if (unitTex != mCommand->mUnitTexMap.end())
	{
		unitTex->second->BindForReading(GL_TEXTURE1, 0);
	}
}

void final_material::SetAttribID(GLuint attribID)
{
	mAttribID = attribID;
}
