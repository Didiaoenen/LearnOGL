#include "LearnOGLMesh.h"

namespace OGL
{
	LearnOGLMesh::LearnOGLMesh(std::vector<oglVertex> vertices, std::vector<uint32_t> indices)
		:mVertices(vertices), mIndices(indices)
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

		glEnableVertexAttribArray((GLuint)oglAttrib::Position);
		glVertexAttribPointer((GLuint)oglAttrib::Position, 3, GL_FLOAT, GL_FALSE, sizeof(oglVertex), (void*)0);

		glEnableVertexAttribArray((GLuint)oglAttrib::Normal);
		glVertexAttribPointer((GLuint)oglAttrib::Normal, 3, GL_FLOAT, GL_FALSE, sizeof(oglVertex), (void*)offsetof(oglVertex, oglVertex::normal));

		glEnableVertexAttribArray((GLuint)oglAttrib::TexCoords);
		glVertexAttribPointer((GLuint)oglAttrib::TexCoords, 2, GL_FLOAT, GL_FALSE, sizeof(oglVertex), (void*)offsetof(oglVertex, oglVertex::texcoords));

		glEnableVertexAttribArray((GLuint)oglAttrib::Tangent);
		glVertexAttribPointer((GLuint)oglAttrib::Tangent, 3, GL_FLOAT, GL_FALSE, sizeof(oglVertex), (void*)offsetof(oglVertex, oglVertex::tangent));

		glEnableVertexAttribArray((GLuint)oglAttrib::BitTangent);
		glVertexAttribPointer((GLuint)oglAttrib::BitTangent, 3, GL_FLOAT, GL_FALSE, sizeof(oglVertex), (void*)offsetof(oglVertex, oglVertex::bittangent));

		glBindVertexArray(0);
	}
}