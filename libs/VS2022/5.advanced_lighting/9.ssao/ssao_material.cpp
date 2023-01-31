#include "ssao_material.h"

ssao_material::ssao_material()
{
}

ssao_material::ssao_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mPosLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mNormalLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
	mShader->SetTexUnit(mTexNoiseLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x02);
}

ssao_material::~ssao_material()
{
}

void ssao_material::Draw()
{
	mShader->Use();
}

void ssao_material::DrawByIndex(GLuint index, GLenum texIndex/* = GL_TEXTURE0*/)
{
	mShader->Use();

	CommandDrawByIndex(index, texIndex);
}

void ssao_material::SetAttribID(GLuint attrib)
{
	mAttribID = attrib;
}

void ssao_material::CommandDrawByIndex(GLuint index, GLenum texIndex/* = GL_TEXTURE0*/)
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