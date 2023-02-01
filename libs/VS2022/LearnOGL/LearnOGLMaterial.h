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
		virtual void SetTexture(LearnOGLTexture* texture);
		virtual void BindTextures(uint32_t count);

		GLuint GetAttribID(std::string strLoc);

	public:
		LearnOGLShader* mShader{ nullptr };
		LearnOGLCommand* mCommand{ nullptr };
	};
}