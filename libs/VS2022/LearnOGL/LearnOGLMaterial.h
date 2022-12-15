#pragma once

#include "LearnOGLDefine.h"
#include "LearnOGLShader.h"
#include "LearnOGLTexture.h"

namespace OGL
{
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