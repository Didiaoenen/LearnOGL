#include "LearnOGLFBO.h"

namespace OGL
{
	LearnOGLFBO::LearnOGLFBO()
	{
	}

	LearnOGLFBO::LearnOGLFBO(uint32_t width, uint32_t height) :
		mWidth(width),
		mHeight(height)
	{
	}

	LearnOGLFBO::~LearnOGLFBO()
	{
	}
	
	void LearnOGLFBO::BindForRead()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, mFBO);
	}

	void LearnOGLFBO::UnBindForWrite()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}