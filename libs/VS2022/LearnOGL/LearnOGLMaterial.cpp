#include "LearnOGLMaterial.h"

namespace OGL
{
	LearnOGLMaterial::LearnOGLMaterial() :
		mShader(nullptr),
		mCommand(nullptr)
	{
	}

	LearnOGLMaterial::LearnOGLMaterial(LearnOGLShader* shader) : 
		mShader(shader),
		mCommand(nullptr)
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
}
