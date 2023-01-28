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

void blur_material::FirstDraw()
{
	mShader->Use();

	DrawByIndex(1);
}

uint32_t blur_material::DrawByIndex(uint32_t index)
{
	int textureIndex = 0;
	if (mCommand)
	{
		auto unitText = mCommand->mUnitTexMap.find(mAttribID);
		if (unitText != mCommand->mUnitTexMap.end())
		{
			unitText->second->BindForReading(GL_TEXTURE0, index);
			textureIndex++;
		}
	}
	return textureIndex;
}

void blur_material::Draw()
{
	mShader->Use();

	int textureIndex = 0;
	textureIndex += DrawByIndex(0);

	if (mImageTex)
	{
		mImageTex->Bind(GL_TEXTURE0 + textureIndex);
	}
}

void blur_material::SetAttribID(GLuint attribID)
{
	mAttribID = attribID;
}
