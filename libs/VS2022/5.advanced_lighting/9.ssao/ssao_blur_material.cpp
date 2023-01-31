#include "ssao_blur_material.h"

ssao_blur_material::ssao_blur_material()
{
}

ssao_blur_material::ssao_blur_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mSSAOLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
}

ssao_blur_material::~ssao_blur_material()
{
	mShader->Use();

}

void ssao_blur_material::DrawByIndex(GLuint index, GLenum texIndex/* = GL_TEXTURE0*/)
{
	mShader->Use();

	CommandDrawByIndex(index, texIndex);
}

void ssao_blur_material::SetAttribID(GLuint attrib)
{
	mAttribID = attrib;
}

void ssao_blur_material::CommandDrawByIndex(GLuint index, GLenum texIndex/* = GL_TEXTURE0*/)
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
