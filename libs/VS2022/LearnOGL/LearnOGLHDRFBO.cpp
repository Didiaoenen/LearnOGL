#include "LearnOGLHDRFBO.h"

namespace OGL
{
	OGL::LearnOGLHDRFBO::LearnOGLHDRFBO()
	{
	}

	LearnOGLHDRFBO::LearnOGLHDRFBO(uint32_t weight, uint32_t height) :
		LearnOGLFBO(weight, height)
	{
		Init(weight, height);
	}

	LearnOGLHDRFBO::~LearnOGLHDRFBO()
	{
	}

	void LearnOGLHDRFBO::BindForWriting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	}

	void LearnOGLHDRFBO::UnbindForWriting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void LearnOGLHDRFBO::BindForReading(GLenum textureUnit/* = GL_TEXTURE0*/)
	{
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, mColorTex);
	}

	bool LearnOGLHDRFBO::Init(uint32_t width, uint32_t height)
	{
		glGenFramebuffers(1, &mFBO);

		glGenTextures(1, &mColorTex);
		glBindTexture(GL_TEXTURE_2D, mColorTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glGenRenderbuffers(1, &mDepthRBO);
		glBindRenderbuffer(GL_RENDERBUFFER, mDepthRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);

		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mColorTex, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthRBO);

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