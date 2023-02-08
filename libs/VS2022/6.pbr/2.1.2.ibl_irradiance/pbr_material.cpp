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
}

void pbr_material::DrawByIndex(GLuint index, GLenum texIndex)
{
	mShader->Use();

	CommandDrawByIndex(index, texIndex);
}

void pbr_material::SetAttribID(GLuint attrib)
{
	mAttribID = attrib;
}

void pbr_material::CommandDrawByIndex(GLuint index, GLenum texIndex)
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
