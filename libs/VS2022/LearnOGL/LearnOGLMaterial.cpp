#include "LearnOGLMaterial.h"

namespace OGL
{
	LearnOGLMaterial::LearnOGLMaterial()
	{
	}

	LearnOGLMaterial::LearnOGLMaterial(LearnOGLShader* shader) : 
		mShader(shader)
	{
	}

	LearnOGLMaterial::~LearnOGLMaterial()
	{
	}

	void LearnOGLMaterial::Draw()
	{
	}

	GLuint LearnOGLMaterial::GetAttribID(std::string strLoc)
	{
		return mShader->GetUniformLocation(strLoc);
	}

	void LearnOGLMaterial::SetAttribID(GLuint attribID)
	{
	}
}
