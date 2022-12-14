#pragma once

#include <glad/glad.h>

#include <iostream>

namespace OGL
{
	class LearnOGLDepthFBO
	{
	public:
		LearnOGLDepthFBO();
		LearnOGLDepthFBO(uint32_t width, uint32_t height);
		~LearnOGLDepthFBO();

		void BindForWriting();
		void UnbindForWriting();

		void BindForReading(GLenum textureUnit = GL_TEXTURE0);

	public:

		uint32_t mWidth;
		uint32_t mHeight;

	private:

		bool Init(uint32_t width, uint32_t height);

	private:

		GLuint mFBO;
		GLuint mDepthTex;

	};
}