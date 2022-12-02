#pragma once

#include "LearnOGLTexture.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>

struct oglVertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 tangent;
	glm::vec3 bitTangent;
	glm::vec2 texcoords;
};

class LearnOGLMesh
{
public:
	LearnOGLMesh(std::vector<oglVertex> vertices, std::vector<UINT> indices, std::vector<LearnOGLTexture> textures);
	~LearnOGLMesh();

private:
};

