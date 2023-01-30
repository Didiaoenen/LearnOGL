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
		virtual void DrawByIndex(GLuint index, GLenum texIndex = GL_TEXTURE0);
		virtual void SetAttribID(GLuint attribID);

		GLuint GetAttribID(std::string strLoc);

	public:
		LearnOGLShader* mShader{ nullptr };
		LearnOGLCommand* mCommand{ nullptr };
	};
}