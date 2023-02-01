#include "blur_material.h"

blur_material::blur_material()
{
}

blur_material::blur_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mImageTexLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

blur_material::~blur_material()
{
}

void blur_material::Draw()
{
	mShader->Use();

	CommandDrawByIndex(0);
}

void blur_material::DrawByIndex(GLuint index, GLenum texIndex/* = GL_TEXTURE0*/)
{
	mShader->Use();

	CommandDrawByIndex(index, texIndex);
}

void blur_material::SetAttribID(GLuint attribID)
{
	mAttribID = attribID;
}

void blur_material::CommandDrawByIndex(GLuint index, GLenum texIndex/* = GL_TEXTURE0*/)
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
