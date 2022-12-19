#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "LearnOGLBatch.h"

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
		LearnOGLBatch MakeQuad(GLfloat radius);
		LearnOGLBatch MakeCube(GLfloat radius);

	private:

		static LearnOGLTools* mInstance;
	};
}

