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

		LearnOGLBatch MakePlane(GLfloat radius, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		LearnOGLBatch MakeQuad(GLfloat radius, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		LearnOGLBatch MakeCube(GLfloat radius, glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	private:

		static LearnOGLTools* mInstance;
	};
}

