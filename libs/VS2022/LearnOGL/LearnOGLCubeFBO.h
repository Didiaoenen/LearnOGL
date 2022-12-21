#pragma once

#include <glad/glad.h>

#include <string>

namespace OGL
{
	class LearnOGLCubeFBO
	{
	public:
		LearnOGLCubeFBO();
		LearnOGLCubeFBO(GLfloat width, GLfloat height);
		~LearnOGLCubeFBO();

		void BindForWriting();
		void UnbindForWriting();

		void BindForReading(GLenum textureUnit = GL_TEXTURE0);

	private:
		bool Init(uint32_t width, uint32_t height);

	private:

		uint32_t mWidth;
		uint32_t mHeight;

		GLuint mFBO;
		GLuint mCubeDepthTex;

	};
}