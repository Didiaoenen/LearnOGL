#include "LearnOGLBatch.h"

LearnOGLBatch::LearnOGLBatch() :
	mPrimitiveType(0),
	mVAO(0),
	mVertexArray(0),
	mNormalArray(0),
	mColorArray(0),
	mVerts(0),
	pVerts(nullptr),
	pNorms(nullptr),
	pColors(nullptr),
	pVertCount(0)
{
}

LearnOGLBatch::~LearnOGLBatch()
{
}

void LearnOGLBatch::Begin(GLenum primitive, GLuint nVerts, GLuint nTextureUnits)
{
	mPrimitiveType = primitive;
	mVerts = nVerts;

	glGenVertexArrays(1, &mVAO);

}

void LearnOGLBatch::End()
{

}

void LearnOGLBatch::CopyVertexData3f(glm::vec3* vertexs)
{
	if (mVertexArray == 0)
	{
		glGenBuffers(1, &mVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, vertexs, GL_DYNAMIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * mVerts, vertexs);
	}
}

void LearnOGLBatch::CopyNormalData3f(glm::vec3* normals)
{
	if (mNormalArray == 0)
	{
		glGenBuffers(1, &mNormalArray);
		glBindBuffer(GL_ARRAY_BUFFER, mNormalArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, normals, GL_DYNAMIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, mNormalArray);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * mVerts, normals);
	}
}

void LearnOGLBatch::CopyColorData4f(glm::vec3* colors)
{
	if (mColorArray == 0)
	{
		glGenBuffers(1, &mColorArray);
		glBindBuffer(GL_ARRAY_BUFFER, mColorArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * mVerts, colors, GL_DYNAMIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, mColorArray);

		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * mVerts, colors);
	}
}

void LearnOGLBatch::Vertex3f(GLfloat x, GLfloat y, GLfloat z)
{
	if (mVertexArray == 0)
	{
		glGenBuffers(1, &mVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, nullptr, GL_DYNAMIC_DRAW);
	}

	if (!pVerts)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
		pVerts = (glm::vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	if (pVertCount >= mVerts)
	{
		return;
	}

	pVerts[pVertCount][0] = x;
	pVerts[pVertCount][1] = y;
	pVerts[pVertCount][2] = z;
	pVertCount++;
}

void LearnOGLBatch::Vertex3fv(glm::vec3 vertex)
{
	if (mVertexArray == 0)
	{
		glGenBuffers(1, &mVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, nullptr, GL_DYNAMIC_DRAW);
	}

	if (!pVerts)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
		pVerts = (glm::vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	if (pVertCount >= mVerts)
	{
		return;
	}

	pVerts[pVertCount] = vertex;
	pVertCount++;
}

void LearnOGLBatch::Normal3f(GLfloat x, GLfloat y, GLfloat z)
{
	if (mNormalArray == 0)
	{
		glGenBuffers(1, &mNormalArray);
		glBindBuffer(GL_ARRAY_BUFFER, mNormalArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, nullptr, GL_DYNAMIC_DRAW);
	}

	if (!pNorms)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mNormalArray);
		pNorms = (glm::vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	if (pVertCount >= mVerts)
	{
		return;
	}

	pNorms[pVertCount][0] = x;
	pNorms[pVertCount][1] = y;
	pNorms[pVertCount][2] = z;
}

void LearnOGLBatch::Normal3fv(glm::vec3 normal)
{
	if (mNormalArray == 0)
	{
		glGenBuffers(1, &mNormalArray);
		glBindBuffer(GL_ARRAY_BUFFER, mNormalArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, nullptr, GL_DYNAMIC_DRAW);
	}

	if (!pNorms)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mNormalArray);
		pNorms = (glm::vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	if (pVertCount >= mVerts)
	{
		return;
	}

	pNorms[pVertCount] = normal;
}

void LearnOGLBatch::Color4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
{
	if (mColorArray == 0)
	{
		glGenBuffers(1, &mColorArray);
		glBindBuffer(GL_ARRAY_BUFFER, mColorArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * mVerts, nullptr, GL_DYNAMIC_DRAW);
	}

	if (!pColors)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mColorArray);
		pColors = (glm::vec4*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	if (pVertCount > mVerts)
	{
		return;
	}

	pColors[pVertCount][0] = r;
	pColors[pVertCount][1] = g;
	pColors[pVertCount][2] = b;
	pColors[pVertCount][3] = a;
}

void LearnOGLBatch::Color4fv(glm::vec4 color)
{
	if (mColorArray == 0)
	{
		glGenBuffers(1, &mColorArray);
		glBindBuffer(GL_ARRAY_BUFFER, mColorArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * mVerts, nullptr, GL_DYNAMIC_DRAW);
	}

	if (!pColors)
	{
		glBindBuffer(GL_ARRAY_BUFFER, mColorArray);
		pColors = (glm::vec4*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	if (pVertCount >= mVerts)
	{
		return;
	}

	pColors[pVertCount] = color;
}
