#include "ssao_lighting_material.h"

ssao_lighting_material::ssao_lighting_material()
{
}

ssao_lighting_material::ssao_lighting_material(OGL::LearnOGLShader* shader) :
	OGL::LearnOGLMaterial(shader)
{
	mShader->Use();
	mShader->SetTexUnit(mPosLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x00);
	mShader->SetTexUnit(mNormalLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x01);
	mShader->SetTexUnit(mAlbedoLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x02);
	mShader->SetTexUnit(mSSAOLoc, (uint32_t)OGL::TexCoordIndex::TexCoord0x03);
}

ssao_lighting_material::~ssao_lighting_material()
{
}

void ssao_lighting_material::Draw()
{
	mShader->Use();
}

void ssao_lighting_material::DrawByIndex(GLuint index, GLenum texIndex/* = GL_TEXTURE0*/)
{
	mShader->Use();

	CommandDrawByIndex(index, texIndex);
}

void ssao_lighting_material::SetAttribID(GLuint attrib)
{
	if (mAttribMap.find(attrib) == mAttribMap.end())
	{
		mAttribMap.insert(std::pair<GLuint, bool>(attrib, true));

		if (mCommand)
		{
			auto unitText = mCommand->mUnitTexMap.find(attrib);
			if (unitText != mCommand->mUnitTexMap.end())
			{
				auto fbo = dynamic_cast<OGL::LearnOGLCustomFBO*>(unitText->second);
				for (uint32_t i = 0; i < fbo->mColorAttchCount; i++)
				{
					mDrawTexMap.insert(std::pair<uint32_t, OGL::DrawTex*>(mDrawTexMap.size(), new OGL::DrawTex(fbo, i)));
				}
			}
		}
	}
}

void ssao_lighting_material::CommandDrawByIndex(GLuint index, GLenum texIndex/* = GL_TEXTURE0*/)
{
	if (mDrawTexMap.find(index) != mDrawTexMap.end())
	{
		auto drawTex = mDrawTexMap.find(index)->second;
		drawTex->mFBO->BindForReading(texIndex, drawTex->mIndex);
	}
}
