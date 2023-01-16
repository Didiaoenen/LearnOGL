#pragma once

#include "LearnOGLFBO.h"

namespace OGL
{
	class LearnOGLHDRFBO : public LearnOGLFBO
	{
	public:
		LearnOGLHDRFBO();
		LearnOGLHDRFBO(uint32_t weight, uint32_t height);
		~LearnOGLHDRFBO();

		virtual void BindForWriting() override;
		virtual void UnbindForWriting() override;

		virtual void BindForReading(GLenum textureUnit = GL_TEXTURE0) override;

	private:
		bool Init(uint32_t width, uint32_t height);

	private:
		GLuint mColorTex{ 0 };
		GLuint mDepthRBO{ 0 };

	};
}