#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "LearnOGLDefine.h"

#include <vector>

namespace OGL
{
	class LearnOGLMesh
	{
	public:
		LearnOGLMesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
		~LearnOGLMesh();

		void Draw();

	public:
		std::vector<Vertex> mVertices;
		std::vector<uint32_t> mIndices;

	private:
		void SetupMesh();

		GLuint mVAO;
		GLuint mVBO;
		GLuint mEBO;
	};
}

