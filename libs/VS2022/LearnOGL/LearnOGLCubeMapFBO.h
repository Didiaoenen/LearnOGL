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
		LearnOGLCubeMapFBO(uint32_t width, uint32_t height, AttachType type = AttachType::COLOR, bool depthAttach = false, uint32_t depths = 32);
		~LearnOGLCubeMapFBO();

		virtual void BindForWriting() override;
		virtual void UnbindForWriting() override;

		virtual void BindForReading(GLenum textureUnit = GL_TEXTURE0, uint32_t colorIndex = 0) override;

	private:
		bool Init(uint32_t width, uint32_t height);

	private:
		GLuint mCubeMapTex{ 0 };
		GLuint mDepthRBO{ 0 };

		AttachType mType{ (AttachType)0 };
		bool mDepthAttach{ false };
		uint32_t mDepths{ 0 };
	};
}