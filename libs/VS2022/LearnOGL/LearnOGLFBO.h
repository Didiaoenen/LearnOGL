#pragma once

#include <glad/glad.h>

#include <iostream>

namespace OGL
{
	class LearnOGLFBO
	{
	public:
		LearnOGLFBO();
		LearnOGLFBO(uint32_t width, uint32_t height);
		virtual ~LearnOGLFBO();

		virtual void BindForWriting() = 0;
		virtual void UnbindForWriting() = 0;

		virtual void BindForReading(GLenum textureUnit = GL_TEXTURE0) = 0;

	public:
		uint32_t mWidth;
		uint32_t mHeight;

	protected:
		GLuint mFBO;

	};
}