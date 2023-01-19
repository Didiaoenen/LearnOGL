#include "LearnOGLCustomFBO.h"

namespace OGL
{
	LearnOGLCustomFBO::LearnOGLCustomFBO()
	{
	}

	LearnOGLCustomFBO::LearnOGLCustomFBO(uint32_t width, uint32_t height, uint32_t colorAttachCount, bool depthAttach, bool stencilAttach) :
		OGL::LearnOGLFBO(width, height)
	{
		mColorAttchCount = colorAttachCount;
		mDepthAttach = depthAttach;
		mStencilAttach = stencilAttach;
		
		mColorTexs = new GLuint[mColorAttchCount];

		Init(width, height);
	}

	LearnOGLCustomFBO::~LearnOGLCustomFBO()
	{
	}

	void LearnOGLCustomFBO::BindForWriting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	}

	void LearnOGLCustomFBO::UnbindForWriting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void LearnOGLCustomFBO::BindForReading(GLenum textureUnit/* = GL_TEXTURE0*/, uint32_t colorIndex/* = 0*/)
	{
		if (colorIndex < mColorAttchCount)
		{
			glActiveTexture(textureUnit);
			glBindTexture(GL_TEXTURE_2D, mColorTexs[colorIndex]);
		}
	}

	bool OGL::LearnOGLCustomFBO::Init(uint32_t width, uint32_t height)
	{
		glGenFramebuffers(1, &mFBO);
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);

		glGenTextures(2, mColorTexs);
		for (uint32_t i = 0; i < mColorAttchCount; i++)
		{
			glBindTexture(GL_TEXTURE_2D, mColorTexs[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, mColorTexs[i], 0);
		}

		GLenum* attachments = new GLenum[mColorAttchCount];
		for (uint32_t i = 0; i < mColorAttchCount; i++)
		{
			attachments[i] = GL_COLOR_ATTACHMENT0 + i;
		}
		glDrawBuffers(mColorAttchCount, attachments);
		delete[] attachments;

		if (mDepthAttach)
		{
			glGenRenderbuffers(1, &mDepthRBO);
			glBindRenderbuffer(GL_RENDERBUFFER, mDepthRBO);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthRBO);
		}

		if (mStencilAttach)
		{
			glGenRenderbuffers(1, &mStencilRBO);
		}

		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout << "Error::FBO status: " << status << std::endl;
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return false;
	}
}