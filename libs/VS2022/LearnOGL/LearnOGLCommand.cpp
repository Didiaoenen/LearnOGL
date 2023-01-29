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
		if (mUnitTexMap.find(id) == mUnitTexMap.end())
		{
			auto fbo = new LearnOGLDepthFBO(width, height);
			mUnitTexMap.insert(std::pair<GLuint, LearnOGLFBO*>(id, fbo));
			return fbo;
		}
		return nullptr;
	}

	LearnOGLFBO* LearnOGLCommand::GetTemporaryHDRRT(GLuint id, GLuint width, GLuint height)
	{
		if (mUnitTexMap.find(id) == mUnitTexMap.end())
		{
			auto fbo = new LearnOGLHDRFBO(width, height);
			mUnitTexMap.insert(std::pair<GLuint, LearnOGLFBO*>(id, fbo));
			return fbo;
		}
		return nullptr;
	}

	LearnOGLFBO* LearnOGLCommand::GetTemporaryCubeMapRT(GLuint id, GLuint width, GLuint height)
	{
		if (mUnitTexMap.find(id) == mUnitTexMap.end())
		{
			auto fbo = new LearnOGLCubeMapFBO(width, height);
			mUnitTexMap.insert(std::pair<GLuint, LearnOGLFBO*>(id, fbo));
			return fbo;
		}
		return nullptr;
	}

	LearnOGLFBO* LearnOGLCommand::GetTemporaryCustomRT(GLuint id, GLuint width, GLuint height, uint32_t colorAttachCount, bool depthAttch, bool stencilAttach)
	{
		if (mUnitTexMap.find(id) == mUnitTexMap.end())
		{
			auto fbo = new LearnOGLCustomFBO(width, height, colorAttachCount, depthAttch, stencilAttach);
			mUnitTexMap.insert(std::pair<GLuint, LearnOGLFBO*>(id, fbo));
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
		if (mUnitTexMap.find(id) != mUnitTexMap.end())
		{
			mUnitTexMap.find(id)->second->BindForWriting();
		}
	}

	void LearnOGLCommand::SetReadTarget(GLuint id)
	{
		if (mUnitTexMap.find(id) != mUnitTexMap.end())
		{
			mUnitTexMap.find(id)->second->BindForRead();
		}
	}

	void LearnOGLCommand::SetUnWriteTarget(GLuint id)
	{
		if (mUnitTexMap.find(id) != mUnitTexMap.end())
		{
			mUnitTexMap.find(id)->second->UnBindForWrite();
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

	void LearnOGLCommand::UnBindFramebuffer()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void LearnOGLCommand::ReleaseTemporaryRT(GLuint id)
	{
		if (mUnitTexMap.find(id) != mUnitTexMap.end())
		{
			mUnitTexMap.find(id)->second->UnbindForWriting();
		}
	}

	void LearnOGLCommand::BlitDepthFBO(GLfloat width, GLfloat height)
	{
		glBlitFramebuffer(0, 0, width, height, 0, 0, width, height, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	}

	void LearnOGLCommand::Clear()
	{
		mColorBit = false;
		mDepthBit = false;
		mBackgroundColor = glm::vec4(0.0f);
	}
}
