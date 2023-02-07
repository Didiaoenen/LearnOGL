#include "background_material.h"

background_material::background_material()
{
}

background_material::background_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mEnvironmentLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

background_material::~background_material()
{
}

void background_material::Draw()
{
	mShader->Use();
}

void background_material::DrawByIndex(GLuint index, GLenum texIndex)
{
	mShader->Use();

	CommandDrawByIndex(index, texIndex);
}

void background_material::SetAttribID(GLuint attrib)
{
	mAttribID = attrib;
}

void background_material::CommandDrawByIndex(GLuint index, GLenum texIndex)
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
