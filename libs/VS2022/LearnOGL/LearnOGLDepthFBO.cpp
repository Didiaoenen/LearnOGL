#include "LearnOGLDepthFBO.h"

namespace OGL
{
	OGL::LearnOGLDepthFBO::LearnOGLDepthFBO() :
		mWidth(0),
		mHeight(0),
		mFBO(0),
		mDepthTex(0)
	{
	}

	OGL::LearnOGLDepthFBO::LearnOGLDepthFBO(uint32_t width, uint32_t height) :
		mWidth(width),
		mHeight(height),
		mFBO(0),
		mDepthTex(0)
	{
		Init(width, height);
	}

	OGL::LearnOGLDepthFBO::~LearnOGLDepthFBO()
	{
	}

	void OGL::LearnOGLDepthFBO::BindForWriting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	}

	void LearnOGLDepthFBO::UnbindForWriting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OGL::LearnOGLDepthFBO::BindForReading(GLenum textureUnit/* = GL_TEXTURE0*/)
	{
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, mDepthTex);
	}

	bool OGL::LearnOGLDepthFBO::Init(uint32_t width, uint32_t height)
	{
		glGenFramebuffers(1, &mFBO);

		glGenTextures(1, &mDepthTex);
		glBindTexture(GL_TEXTURE_2D, mDepthTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, &mBoraderColor[0]);

		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthTex, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "Error::FBO status: " << status << std::endl;
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return true;
	}
}