#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "LearnOGLBatch.h"
#include "LearnOGLTexture.h"

#include <random>
#include <iostream>

namespace OGL
{
	class LearnOGLTools
	{
	public:
		LearnOGLTools();
		~LearnOGLTools();

		static LearnOGLTools* Instance();

		LearnOGLBatch MakePlane(GLfloat radius);
		LearnOGLBatch MakeCube(GLfloat radius);
		LearnOGLBatch MakeQuad(GLfloat radius, bool tangent = false, bool bitangent = false);

		LearnOGLTexture* MakeRandomNoiseTex(GLuint width, GLuint height);

	private:

		static LearnOGLTools* mInstance;
	};
}

