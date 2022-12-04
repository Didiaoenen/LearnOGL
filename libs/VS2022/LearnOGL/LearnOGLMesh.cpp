#include "LearnOGLMesh.h"

namespace OGL
{
	LearnOGLMesh::LearnOGLMesh(std::vector<oglVertex> vertices, std::vector<uint32_t> indices, std::vector<LearnOGLTexture> textures)
	{
		SetupMesh();
	}

	LearnOGLMesh::~LearnOGLMesh()
	{
	}

	void LearnOGLMesh::Draw()
	{
		glBindVertexArray(mVAO);
		glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(mIndices.size()), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void LearnOGLMesh::SetupMesh()
	{
		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mEBO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(oglVertex), &mVertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(uint32_t), &mIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray(oglAttrib::Position);
		glVertexAttribPointer(oglAttrib::Position, 3, GL_FLOAT, GL_FALSE, sizeof(oglVertex), (void*)0);

		glEnableVertexAttribArray(oglAttrib::Normal);
		glVertexAttribPointer(oglAttrib::Normal, 3, GL_FLOAT, GL_FALSE, sizeof(oglVertex), (void*)offsetof(oglVertex, oglVertex::normal));

		glEnableVertexAttribArray(oglAttrib::TexCoords);
		glVertexAttribPointer(oglAttrib::TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(oglVertex), (void*)offsetof(oglVertex, oglVertex::texcoords));

		glEnableVertexAttribArray(oglAttrib::Tangent);
		glVertexAttribPointer(oglAttrib::Tangent, 3, GL_FLOAT, GL_FALSE, sizeof(oglVertex), (void*)offsetof(oglVertex, oglVertex::tangent));

		glEnableVertexAttribArray(oglAttrib::BitTangent);
		glVertexAttribPointer(oglAttrib::BitTangent, 3, GL_FLOAT, GL_FALSE, sizeof(oglVertex), (void*)offsetof(oglVertex, oglVertex::bittangent));

		glBindVertexArray(0);
	}
}