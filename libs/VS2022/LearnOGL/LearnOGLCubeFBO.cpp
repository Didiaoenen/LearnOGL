#include "LearnOGLCubeFBO.h"

namespace OGL
{
	OGL::LearnOGLCubeFBO::LearnOGLCubeFBO()
	{
	}

	LearnOGLCubeFBO::LearnOGLCubeFBO(GLfloat width, GLfloat height)
	{
		Init(width, height);
	}

	LearnOGLCubeFBO::~LearnOGLCubeFBO()
	{
	}

	void LearnOGLCubeFBO::BindForWriting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	}

	void LearnOGLCubeFBO::UnbindForWriting()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void LearnOGLCubeFBO::BindForReading(GLenum textureUnit)
	{
		glActiveTexture(textureUnit);
		glBindTexture(GL_TEXTURE_2D, mCubeDepthTex);
	}

	bool LearnOGLCubeFBO::Init(uint32_t width, uint32_t height)
	{
		glGenFramebuffers(1, &mFBO);

		glGenTextures(1, &mCubeDepthTex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mCubeDepthTex);
		for (uint32_t i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, mCubeDepthTex, 0);
		
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return true;
	}

}