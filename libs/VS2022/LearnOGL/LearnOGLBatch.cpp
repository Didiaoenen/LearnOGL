#include "LearnOGLBatch.h"

namespace OGL
{
	LearnOGLBatch::LearnOGLBatch() :
		mPrimitiveType(0),
		mVerts(0),
		mVAO(0),
		pVertCount(0),
		mBatchDone(false),
		mVertexArray(0),
		mNormalArray(0),
		mTexCoordArray(0),
		pVerts(nullptr),
		pNorms(nullptr),
		pTexCoord(nullptr)
	{
	}

	LearnOGLBatch::~LearnOGLBatch()
	{
	}

	void LearnOGLBatch::Begin(GLenum primitive, GLuint verts)
	{
		mPrimitiveType = primitive;
		mVerts = verts;

		glGenVertexArrays(1, &mVAO);
		glBindVertexArray(mVAO);
	}

	void LearnOGLBatch::Next()
	{
		pVertCount++;
	}

	void LearnOGLBatch::End()
	{
		if (pVerts)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			pVerts = nullptr;
		}

		if (pNorms)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mNormalArray);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			pNorms = nullptr;
		}

		if (pTexCoord)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordArray);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			pTexCoord = nullptr;
		}

		glBindVertexArray(mVAO);

		if (mVertexArray > 0)
		{
			glEnableVertexAttribArray((GLuint)oglBatchAttrib::Position);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
			glVertexAttribPointer((GLuint)oglBatchAttrib::Position, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if (mNormalArray > 0)
		{
			glEnableVertexAttribArray((GLuint)oglBatchAttrib::Normal);
			glBindBuffer(GL_ARRAY_BUFFER, mNormalArray);
			glVertexAttribPointer((GLuint)oglBatchAttrib::Normal, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if (mTexCoordArray > 0)
		{
			glEnableVertexAttribArray((GLuint)oglBatchAttrib::TexCoord);
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordArray);
			glVertexAttribPointer((GLuint)oglBatchAttrib::TexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		mBatchDone = true;
		glBindVertexArray(0);
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

	void LearnOGLBatch::CopyTexCoordData2f(glm::vec2* texcoord)
	{
		if (mTexCoordArray == 0)
		{
			glGenBuffers(1, &mTexCoordArray);
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * mVerts, texcoord, GL_DYNAMIC_DRAW);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordArray);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * mVerts, texcoord);
		}
	}

	void LearnOGLBatch::Vertex3f(GLfloat x, GLfloat y, GLfloat z)
	{
		if (mVertexArray == 0)
		{
			glGenBuffers(1, &mVertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, NULL, GL_DYNAMIC_DRAW);
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

		pVerts[pVertCount].x = x;
		pVerts[pVertCount].y = y;
		pVerts[pVertCount].z = z;
	}

	void LearnOGLBatch::Vertex3fv(glm::vec3 vertex)
	{
		if (mVertexArray == 0)
		{
			glGenBuffers(1, &mVertexArray);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, NULL, GL_DYNAMIC_DRAW);
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

		pVerts = &vertex;
	}

	void LearnOGLBatch::Normal3f(GLfloat x, GLfloat y, GLfloat z)
	{
		if (mNormalArray == 0)
		{
			glGenBuffers(1, &mNormalArray);
			glBindBuffer(GL_ARRAY_BUFFER, mNormalArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, NULL, GL_DYNAMIC_DRAW);
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

		pNorms[pVertCount].x = x;
		pNorms[pVertCount].y = y;
		pNorms[pVertCount].z = z;
	}

	void LearnOGLBatch::Normal3fv(glm::vec3 normal)
	{
		if (mNormalArray == 0)
		{
			glGenBuffers(1, &mNormalArray);
			glBindBuffer(GL_ARRAY_BUFFER, mNormalArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, NULL, GL_DYNAMIC_DRAW);
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

		pNorms = &normal;
	}

	void LearnOGLBatch::TexCoord2f(GLclampf s, GLclampf t)
	{
		if (mTexCoordArray == 0)
		{
			glGenBuffers(1, &mTexCoordArray);
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * mVerts, NULL, GL_DYNAMIC_DRAW);
		}

		if (!pTexCoord)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordArray);
			pTexCoord = (glm::vec2*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		if (pVertCount >= mVerts)
		{
			return;
		}

		pTexCoord[pVertCount].s = s;
		pTexCoord[pVertCount].t = t;
	}

	void LearnOGLBatch::TexCoord2fv(glm::vec2 texcoord)
	{
		if (mTexCoordArray == 0)
		{
			glGenBuffers(1, &mTexCoordArray);
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * mVerts, NULL, GL_DYNAMIC_DRAW);
		}

		if (!pTexCoord)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordArray);
			pTexCoord = (glm::vec2*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		if (pVertCount >= mVerts)
		{
			return;
		}

		pTexCoord = &texcoord;
	}

	void LearnOGLBatch::Draw()
	{
		if (!mBatchDone)
		{
			return;
		}

		for (uint32_t i = 0; i < mMaterials.size(); i++)
		{
			mMaterials[i]->Draw();
		}

		glBindVertexArray(mVAO);
		glDrawArrays(mPrimitiveType, 0, mVerts);
		glBindVertexArray(0);
	}
}