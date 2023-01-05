#include "LearnOGLCommand.h"

namespace OGL
{
	LearnOGLCommand::LearnOGLCommand() :
		mDepthBit(false),
		mColorBit(false)
	{
	}

	LearnOGLCommand::LearnOGLCommand(std::string name) :
		mName(name),
		mDepthBit(false),
		mColorBit(false)
	{
		mName = name;
	}

	LearnOGLCommand::~LearnOGLCommand()
	{
	}

	void LearnOGLCommand::GetTemporaryRT(GLuint id, GLuint width, GLuint height)
	{
		if (mUintTexMap.find(id) == mUintTexMap.end())
		{
			mUintTexMap.insert(std::pair<GLuint, LearnOGLFBO*>(id, new LearnOGLDepthFBO(width, height)));
		}
	}

	void LearnOGLCommand::GetTemporaryCubeMapRT(GLuint id, GLuint width, GLuint height)
	{
		if (mUintTexMap.find(id) == mUintTexMap.end())
		{
			mUintTexMap.insert(std::pair<GLuint, LearnOGLFBO*>(id, new LearnOGLCubeMapFBO(width, height)));
		}
	}

	void LearnOGLCommand::ClearRenderTarget(bool depth, bool color, glm::vec4 backgroundcolor)
	{
		mDepthBit = depth;
		mColorBit = color;
		mBackgroundColor = backgroundcolor;
	}

	void LearnOGLCommand::SetRenderTarget(GLuint id)
	{
		if (mUintTexMap.find(id) != mUintTexMap.end())
		{
			mUintTexMap.find(id)->second->BindForWriting();
		}
	}

	void LearnOGLCommand::SetGloablInt(GLuint id, GLint value)
	{
	}

	void LearnOGLCommand::SetGloablIntArray(GLuint id, GLint* value)
	{
	}

	void LearnOGLCommand::SetGloablFloat(GLuint id, GLfloat value)
	{
	}

	void LearnOGLCommand::SetGloablFloatArray(GLuint id, GLfloat* value)
	{
	}

	void LearnOGLCommand::SetGlobalVector(GLuint id, glm::vec4 vec)
	{
	}

	void LearnOGLCommand::SetGlobalVectorArray(GLuint id, glm::vec4* vec)
	{
	}

	void LearnOGLCommand::SetGlobalMatrix(GLuint id, glm::mat4 vec)
	{
	}

	void LearnOGLCommand::SetGlobalMatrixArray(GLuint id, glm::mat4* vec)
	{
	}

	void LearnOGLCommand::SetViewport(GLfloat beginX, GLfloat beginY, GLfloat width, GLfloat height)
	{
		glViewport(beginX, beginY, width, height);
	}

	void LearnOGLCommand::EnableCullFace(bool face)
	{
		return face ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
	}

	void LearnOGLCommand::ReleaseTemporaryRT(GLuint id)
	{
		if (mUintTexMap.find(id) != mUintTexMap.end())
		{
			mUintTexMap.find(id)->second->UnbindForWriting();
		}
	}

	void LearnOGLCommand::Clear()
	{
		mColorBit = false;
		mDepthBit = false;
		mBackgroundColor = glm::vec4(0.0f);
	}
}
