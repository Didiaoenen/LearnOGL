#include "LearnOGLCommand.h"

namespace OGL
{
	LearnOGLCommand::LearnOGLCommand()
	{
	}

	LearnOGLCommand::LearnOGLCommand(std::string name) :
		mName(name)
	{
	}

	LearnOGLCommand::~LearnOGLCommand()
	{
	}

	LearnOGLFBO* LearnOGLCommand::GetTemporaryRT(GLuint id, GLuint width, GLuint height)
	{
		if (mUintTexMap.find(id) == mUintTexMap.end())
		{
			auto fbo = new LearnOGLDepthFBO(width, height);
			mUintTexMap.insert(std::pair<GLuint, LearnOGLFBO*>(id, fbo));
			return fbo;
		}
		return nullptr;
	}

	LearnOGLFBO* LearnOGLCommand::GetTemporaryHDRRT(GLuint id, GLuint width, GLuint height)
	{
		if (mUintTexMap.find(id) == mUintTexMap.end())
		{
			auto fbo = new LearnOGLHDRFBO(width, height);
			mUintTexMap.insert(std::pair<GLuint, LearnOGLFBO*>(id, fbo));
			return fbo;
		}
		return nullptr;
	}

	LearnOGLFBO* LearnOGLCommand::GetTemporaryCubeMapRT(GLuint id, GLuint width, GLuint height)
	{
		if (mUintTexMap.find(id) == mUintTexMap.end())
		{
			auto fbo = new LearnOGLCubeMapFBO(width, height);
			mUintTexMap.insert(std::pair<GLuint, LearnOGLFBO*>(id, fbo));
			return fbo;
		}
		return nullptr;
	}

	LearnOGLFBO* LearnOGLCommand::GetTemporaryCustomRT(GLuint id, GLuint width, GLuint height, uint32_t colorAttachCount, bool depthAttch, bool stencilAttach)
	{
		if (mUintTexMap.find(id) == mUintTexMap.end())
		{
			auto fbo = new LearnOGLCustomFBO(width, height, colorAttachCount, depthAttch, stencilAttach);
			mUintTexMap.insert(std::pair<GLuint, LearnOGLFBO*>(id, fbo));
			return fbo;
		}
		return nullptr;
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
