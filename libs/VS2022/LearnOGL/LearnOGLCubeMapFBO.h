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
		LearnOGLCubeMapFBO(uint32_t width, uint32_t height, AttachType type = AttachType::COLOR, bool depthAttach = false, uint32_t depths = 32, bool clear = false);
		~LearnOGLCubeMapFBO();

		virtual void BindForWriting() override;
		virtual void UnbindForWriting() override;

		virtual void BindForReading(GLenum textureUnit = GL_TEXTURE0, uint32_t colorIndex = 0) override;

		GLuint GetDepthFormat();
		void SetDepthRBO(GLuint id);

	private:
		bool Init(uint32_t width, uint32_t height);

	public:
		GLuint mCubeMapTex{ 0 };
		AttachType mType{ (AttachType)0 };

	private:
		bool mDepthAttach{ false };
		bool mClear{ 0 };
		uint32_t mDepths{ 0 };
	};
}