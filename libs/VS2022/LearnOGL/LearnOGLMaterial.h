#pragma once

#include "LearnOGLShader.h"
#include "LearnOGLTexture.h"

namespace OGL
{
	enum class TexCoord
	{
		TexCoord0x00,
		TexCoord0x01,
		TexCoord0x02,
		TexCoord0x03,
	};

	class LearnOGLMaterial
	{
	public:
		LearnOGLMaterial();
		LearnOGLMaterial(LearnOGLShader* shader);
		virtual ~LearnOGLMaterial();

		virtual void Draw();

	public:
		LearnOGLShader* mShader;
	};
}