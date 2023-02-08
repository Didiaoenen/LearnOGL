#include "irradiance_material.h"

irradiance_material::irradiance_material()
{
}

irradiance_material::irradiance_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mEnvironmentLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

irradiance_material::~irradiance_material()
{
}

void irradiance_material::Draw()
{
	mShader->Use();
}

void irradiance_material::DrawByIndex(GLuint index, GLenum texIndex)
{
	mShader->Use();

	CommandDrawByIndex(index, texIndex);
}

void irradiance_material::SetAttribID(GLuint attrib)
{
	mAttribID = attrib;
}

void irradiance_material::CommandDrawByIndex(GLuint index, GLenum texIndex)
{
	if (mCommand)
	{
		auto unitText = mCommand->mUnitTexMap.find(mAttribID);
		if (unitText != mCommand->mUnitTexMap.end())
		{
			unitText->second->BindForReading(texIndex, index);
		}
	}
}