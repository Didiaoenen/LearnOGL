#include "LearnOGLCubeMapFBO.h"

namespace OGL
{
	OGL::LearnOGLCubeMapFBO::LearnOGLCubeMapFBO()
	{
	}

	LearnOGLCubeMapFBO::LearnOGLCubeMapFBO(uint32_t width, uint32_t height, AttachType type ,bool depthAttach/* = false*/, uint32_t depth/* = 32*/) :
		LearnOGLFBO(width, height)
	{
		mType = type;
		mDepthAttach = depthAttach;
		Init(width, height);
	}

	LearnOGLCubeMapFBO::~LearnOGLCubeMapFBO()
	{
	}

	void LearnOGLCubeMapFBO::BindForWriting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	}

	void LearnOGLCubeMapFBO::UnbindForWriting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void LearnOGLCubeMapFBO::BindForReading(GLenum textureUnit/* = GL_TEXTURE0*/, uint32_t colorCount/* = 0*/)
	{
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mCubeMapTex);
	}

	bool LearnOGLCubeMapFBO::Init(uint32_t width, uint32_t height)
	{
		glGenFramebuffers(1, &mFBO);

		glGenTextures(1, &mCubeMapTex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mCubeMapTex);
		for (uint32_t i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, (GLenum)mType, mCubeMapTex, 0);
		
		if (mDepthAttach)
		{
			glGenRenderbuffers(1, &mDepthRBO);
			glBindRenderbuffer(GL_RENDERBUFFER, mDepthRBO);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, mDepthRBO);
		}

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return true;
	}

}