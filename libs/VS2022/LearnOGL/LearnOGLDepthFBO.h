#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "LearnOGLFBO.h"

#include <iostream>

namespace OGL
{
	class LearnOGLDepthFBO : public LearnOGLFBO
	{
	public:
		LearnOGLDepthFBO();
		LearnOGLDepthFBO(uint32_t width, uint32_t height);
		~LearnOGLDepthFBO();

		virtual void BindForWriting() override;
		virtual void UnbindForWriting() override;

		virtual void BindForReading(GLenum textureUnit = GL_TEXTURE0) override;

	private:
		bool Init(uint32_t width, uint32_t height);

	private:
		GLuint mDepthTex{ 0 };

		glm::vec4 mBoraderColor = glm::vec4(1.0);
	};
}