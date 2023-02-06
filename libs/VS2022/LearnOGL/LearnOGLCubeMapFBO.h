#pragma once

#include <glad/glad.h>

#include "LearnOGLFBO.h"
#include "LearnOGLDefine.h"

namespace OGL
{
	class LearnOGLCubeMapFBO : public LearnOGLFBO
	{
	public:
		LearnOGLCubeMapFBO();
		LearnOGLCubeMapFBO(uint32_t width, uint32_t height, AttachType type, bool depthAttach = false, uint32_t depth = 32);
		~LearnOGLCubeMapFBO();

		virtual void BindForWriting() override;
		virtual void UnbindForWriting() override;

		virtual void BindForReading(GLenum textureUnit = GL_TEXTURE0, uint32_t colorIndex = 0) override;

	private:
		bool Init(uint32_t width, uint32_t height);

	private:
		GLuint mCubeMapTex{ 0 };
		GLuint mDepthRBO{ 0 };

		AttachType mType;
		bool mDepthAttach;
	};
}