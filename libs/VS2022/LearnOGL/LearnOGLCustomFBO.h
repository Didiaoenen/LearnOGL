#pragma once

#include "LearnOGLFBO.h"

#include <vector>

namespace OGL
{
	class LearnOGLCustomFBO : public OGL::LearnOGLFBO
	{
	public:
		LearnOGLCustomFBO();
		LearnOGLCustomFBO(uint32_t width, uint32_t height, uint32_t colorAttachCount = 1, bool depthAttach = false, bool stencilAttach = true);
		virtual ~LearnOGLCustomFBO();

		virtual void BindForWriting() override;
		virtual void UnbindForWriting() override;

		virtual void BindForReading(GLenum textureUnit = GL_TEXTURE0, uint32_t colorIndex = 0) override;

	private:
		bool Init(uint32_t width, uint32_t height);

	public:
		uint32_t mColorAttchCount{ 0 };
	
		GLuint* mColorTexs{ nullptr };
		GLuint mDepthRBO{ 0 };
		GLuint mStencilRBO{ 0 };

	private:
		bool mDepthAttach{ false };
		bool mStencilAttach{ false };

	};
}

