#include "hdr_material.h"

hdr_material::hdr_material()
{
}

hdr_material::hdr_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mHDRTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mHDRAttribID = mShader->GetUniformLocation(mHDRTexLoc);
}

hdr_material::~hdr_material()
{
}

void hdr_material::Draw()
{
	mShader->Use();
	
	if (mCommand->mUnitTexMap.find(mHDRAttribID) != mCommand->mUnitTexMap.end())
	{
		mCommand->mUnitTexMap.find(mHDRAttribID)->second->BindForReading(GL_TEXTURE0);
	}
}
