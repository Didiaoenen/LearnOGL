#include "LearnOGLMesh.h"

namespace OGL
{
	LearnOGLMesh::LearnOGLMesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices)
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
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void LearnOGLMesh::SetupMesh()
	{
		glGenVertexArrays(1, &mVAO);
		glGenBuffers(1, &mVBO);
		glGenBuffers(1, &mEBO);

		glBindVertexArray(mVAO);
		glBindBuffer(GL_ARRAY_BUFFER, mVBO);
		glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(uint32_t), &mIndices[0], GL_STATIC_DRAW);

		glEnableVertexAttribArray((GLuint)VertAttrib::Position);
		glVertexAttribPointer((GLuint)VertAttrib::Position, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		glEnableVertexAttribArray((GLuint)VertAttrib::Normal);
		glVertexAttribPointer((GLuint)VertAttrib::Normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::normal));

		glEnableVertexAttribArray((GLuint)VertAttrib::TexCoord);
		glVertexAttribPointer((GLuint)VertAttrib::TexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::texcoords));

		glEnableVertexAttribArray((GLuint)VertAttrib::Tangent);
		glVertexAttribPointer((GLuint)VertAttrib::Tangent, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::tangent));

		glEnableVertexAttribArray((GLuint)VertAttrib::BitTangent);
		glVertexAttribPointer((GLuint)VertAttrib::BitTangent, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::bittangent));

		glBindVertexArray(0);
	}
}