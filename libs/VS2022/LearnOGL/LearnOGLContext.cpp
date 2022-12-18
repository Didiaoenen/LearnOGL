#include "LearnOGLContext.h"

namespace OGL
{
	OGL::LearnOGLContext::LearnOGLContext()
	{
	}

	LearnOGLContext::~LearnOGLContext()
	{
	}

	void LearnOGLContext::ExecuteCommand(LearnOGLCommand* command)
	{

		glClearColor(command->mBackgroundColor.r, command->mBackgroundColor.g, command->mBackgroundColor.b, command->mBackgroundColor.a);

		GLenum bit = 0;
		if (command->mColorBit)
		{
			bit |= GL_COLOR_BUFFER_BIT;
		}
		if (command->mDepthBit)
		{
			glEnable(GL_DEPTH_TEST);

			bit |= GL_DEPTH_BUFFER_BIT;
		}
		glClear(bit);
	}

	void LearnOGLContext::DrawRenderers()
	{
	}

	void LearnOGLContext::DrawSkybox(LearnOGLCamera* camera)
	{
	}

	void LearnOGLContext::AddRenderer(LearnOGLModel* renderer)
	{
		mRenderers.push_back(renderer);
	}

}
