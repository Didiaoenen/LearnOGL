#pragma once

#include "LearnOGLDefine.h"
#include "LearnOGLShader.h"
#include "LearnOGLTexture.h"
#include "LearnOGLCommand.h"

#include <string>

namespace OGL
{
	class LearnOGLMaterial
	{
	public:
		LearnOGLMaterial();
		LearnOGLMaterial(LearnOGLShader* shader);
		virtual ~LearnOGLMaterial();

		virtual void Draw();

		GLuint GetAttribID(std::string strLoc);

	public:
		LearnOGLShader* mShader;

		LearnOGLCommand* mCommand;
	};
}