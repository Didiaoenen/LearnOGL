#pragma once

#include <glad/glad.h>

#include "LearnOGLFBO.h"

namespace OGL
{
	class LearnOGLCubeMapFBO : public LearnOGLFBO
	{
	public:
		LearnOGLCubeMapFBO();
		LearnOGLCubeMapFBO(uint32_t width, uint32_t height);
		~LearnOGLCubeMapFBO();

		virtual void BindForWriting() override;
		virtual void UnbindForWriting() override;

		virtual void BindForReading(GLenum textureUnit = GL_TEXTURE0) override;

	private:
		bool Init(uint32_t width, uint32_t height);

	private:
		GLuint mCubeMapTex{ 0 };

	};
}