#include "LearnOGLBatch.h"

namespace OGL
{
	LearnOGLBatch::LearnOGLBatch()
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

		if (pTexCoords)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordsArray);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			pTexCoords = nullptr;
		}

		if (pTangs)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTangentArray);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			pTangs = nullptr;
		}

		if (pBitangs)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mBitangentArray);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			pBitangs = nullptr;
		}

		glBindVertexArray(mVAO);

		if (mVertexArray > 0)
		{
			glEnableVertexAttribArray((GLuint)VertAttrib::Position);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexArray);
			glVertexAttribPointer((GLuint)VertAttrib::Position, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if (mNormalArray > 0)
		{
			glEnableVertexAttribArray((GLuint)VertAttrib::Normal);
			glBindBuffer(GL_ARRAY_BUFFER, mNormalArray);
			glVertexAttribPointer((GLuint)VertAttrib::Normal, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if (mTexCoordsArray > 0)
		{
			glEnableVertexAttribArray((GLuint)VertAttrib::TexCoord);
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordsArray);
			glVertexAttribPointer((GLuint)VertAttrib::TexCoord, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if (mTangentArray > 0)
		{
			glEnableVertexAttribArray((GLuint)VertAttrib::Tangent);
			glBindBuffer(GL_ARRAY_BUFFER, mTangentArray);
			glVertexAttribPointer((GLuint)VertAttrib::Tangent, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if (mBitangentArray > 0)
		{
			glEnableVertexAttribArray((GLuint)VertAttrib::Bitangent);
			glBindBuffer(GL_ARRAY_BUFFER, mBitangentArray);
			glVertexAttribPointer((GLuint)VertAttrib::Bitangent, 3, GL_FLOAT, GL_FALSE, 0, 0);
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

	void LearnOGLBatch::CopyTexCoordData2f(glm::vec2* texcoords)
	{
		if (mTexCoordsArray == 0)
		{
			glGenBuffers(1, &mTexCoordsArray);
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordsArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * mVerts, texcoords, GL_DYNAMIC_DRAW);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordsArray);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * mVerts, texcoords);
		}
	}

	void LearnOGLBatch::CopyTangentData3f(glm::vec3* tangents)
	{
		if (mTangentArray == 0)
		{
			glGenBuffers(1, &mTangentArray);
			glBindBuffer(GL_ARRAY_BUFFER, mTangentArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, tangents, GL_DYNAMIC_DRAW);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTangentArray);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * mVerts, tangents);
		}
	}

	void LearnOGLBatch::CopyBitangentData3f(glm::vec3* bitangents)
	{
		if (mBitangentArray == 0)
		{
			glGenBuffers(1, &mBitangentArray);
			glBindBuffer(GL_ARRAY_BUFFER, mBitangentArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, bitangents, GL_DYNAMIC_DRAW);
		}
		else
		{
			glBindBuffer(GL_ARRAY_BUFFER, mBitangentArray);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * mVerts, bitangents);
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

		pVerts[pVertCount] = vertex;
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

		pNorms[pVertCount] = normal;
	}

	void LearnOGLBatch::TexCoord2f(GLclampf s, GLclampf t)
	{
		if (mTexCoordsArray == 0)
		{
			glGenBuffers(1, &mTexCoordsArray);
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordsArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * mVerts, NULL, GL_DYNAMIC_DRAW);
		}

		if (!pTexCoords)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordsArray);
			pTexCoords = (glm::vec2*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		if (pVertCount >= mVerts)
		{
			return;
		}

		pTexCoords[pVertCount].s = s;
		pTexCoords[pVertCount].t = t;
	}

	void LearnOGLBatch::TexCoord2fv(glm::vec2 texcoord)
	{
		if (mTexCoordsArray == 0)
		{
			glGenBuffers(1, &mTexCoordsArray);
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordsArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * mVerts, NULL, GL_DYNAMIC_DRAW);
		}

		if (!pTexCoords)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTexCoordsArray);
			pTexCoords = (glm::vec2*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		if (pVertCount >= mVerts)
		{
			return;
		}

		pTexCoords[pVertCount] = texcoord;
	}

	void LearnOGLBatch::Tangent3f(GLfloat x, GLfloat y, GLfloat z)
	{
		if (mTangentArray == 0)
		{
			glGenBuffers(1, &mTangentArray);
			glBindBuffer(GL_ARRAY_BUFFER, mTangentArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, NULL, GL_DYNAMIC_DRAW);
		}

		if (!pTangs)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTangentArray);
			pTangs = (glm::vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		if (pVertCount >= mVerts)
		{
			return;
		}

		pTangs[pVertCount].x = x;
		pTangs[pVertCount].y = y;
		pTangs[pVertCount].z = z;
	}

	void LearnOGLBatch::Tangent3fv(glm::vec3 tangent)
	{
		if (mTangentArray == 0)
		{
			glGenBuffers(1, &mTangentArray);
			glBindBuffer(GL_ARRAY_BUFFER, mTangentArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, NULL, GL_DYNAMIC_DRAW);
		}

		if (!pTangs)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mTangentArray);
			pTangs = (glm::vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		if (pVertCount >= mVerts)
		{
			return;
		}

		pTangs[pVertCount] = tangent;
	}

	void LearnOGLBatch::Bitangent3f(GLfloat x, GLfloat y, GLfloat z)
	{
		if (mBitangentArray == 0)
		{
			glGenBuffers(1, &mBitangentArray);
			glBindBuffer(GL_ARRAY_BUFFER, mBitangentArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, NULL, GL_DYNAMIC_DRAW);
		}

		if (!pBitangs)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mBitangentArray);
			pBitangs = (glm::vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		if (pVertCount >= mVerts)
		{
			return;
		}

		pBitangs[pVertCount].x = x;
		pBitangs[pVertCount].y = y;
		pBitangs[pVertCount].z = z;
	}

	void LearnOGLBatch::Bitangent3fv(glm::vec3 bitangent)
	{
		if (mBitangentArray == 0)
		{
			glGenBuffers(1, &mBitangentArray);
			glBindBuffer(GL_ARRAY_BUFFER, mBitangentArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * mVerts, NULL, GL_DYNAMIC_DRAW);
		}

		if (!pBitangs)
		{
			glBindBuffer(GL_ARRAY_BUFFER, mBitangentArray);
			pBitangs = (glm::vec3*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		if (pVertCount >= mVerts)
		{
			return;
		}

		pBitangs[pVertCount] = bitangent;
	}

	void LearnOGLBatch::DrawArrays()
	{
		if (!mBatchDone)
		{
			return;
		}

		glBindVertexArray(mVAO);
		glDrawArrays(mPrimitiveType, 0, mVerts);
		glBindVertexArray(0);
	}

	void LearnOGLBatch::Draw()
	{
		if (!mBatchDone)
		{
			return;
		}

		mMaterial->Draw();

		glBindVertexArray(mVAO);
		glDrawArrays(mPrimitiveType, 0, mVerts);
		glBindVertexArray(0);
	}

	void LearnOGLBatch::ShadowDraw()
	{
		if (!mBatchDone)
		{
			return;
		}

		mShadowMaterial->Draw();

		glBindVertexArray(mVAO);
		glDrawArrays(mPrimitiveType, 0, mVerts);
		glBindVertexArray(0);
	}
}