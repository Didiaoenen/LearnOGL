#pragma once

#include "LearnOGLTexture.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

namespace OGL
{
	struct oglVertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoords;
		glm::vec3 tangent;
		glm::vec3 bittangent;
	};

	enum oglAttrib
	{
		Position = 0,
		Normal,
		TexCoords,
		Tangent,
		BitTangent,
	};

	class LearnOGLMesh
	{
	public:
		LearnOGLMesh(std::vector<oglVertex> vertices, std::vector<uint32_t> indices, std::vector<LearnOGLTexture> textures);
		~LearnOGLMesh();

		void Draw();

	public:
		std::vector<oglVertex> mVertices;
		std::vector<uint32_t> mIndices;

	private:
		void SetupMesh();

		GLuint mVAO;
		GLuint mVBO;
		GLuint mEBO;
	};
}

