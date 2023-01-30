#include "deferred_shading_material.h"

deferred_shading_material::deferred_shading_material()
{
}

deferred_shading_material::deferred_shading_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mPosLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mNormalLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
	mShader->SetTexUnit(mAlbedoLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x02);
}

deferred_shading_material::~deferred_shading_material()
{
}

void deferred_shading_material::Draw()
{
	mShader->Use();
}

void deferred_shading_material::DrawByIndex(GLuint index, GLenum texIndex/* = GL_TEXTURE0*/)
{
	mShader->Use();

	CommandDrawByIndex(index, texIndex);
}

void deferred_shading_material::SetAttribID(GLuint attrib)
{
	mAttribID = attrib;
}

void deferred_shading_material::CommandDrawByIndex(GLuint index, GLenum texIndex/* = GL_TEXTURE0*/)
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
