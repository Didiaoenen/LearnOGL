#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "LearnOGLModel.h"

#include <iostream>
#include <vector>

namespace OGL
{
	class LearnOGLBatch : public LearnOGLModel
	{
	public:
		LearnOGLBatch();
		virtual ~LearnOGLBatch();

		void Begin(GLenum primitive, GLuint verts);

		void Next();

		void End();

		void CopyVertexData3f(glm::vec3* vertexs);
		void CopyNormalData3f(glm::vec3* normals);
		void CopyTexCoordData2f(glm::vec2* texcoords);
		void CopyTangentData3f(glm::vec3* tangents);
		void CopyBitangentData3f(glm::vec3* bitangents);

		void Vertex3f(GLfloat x, GLfloat y, GLfloat z);
		void Vertex3fv(glm::vec3 vertex);

		void Normal3f(GLfloat x, GLfloat y, GLfloat z);
		void Normal3fv(glm::vec3 normal);

		void TexCoord2f(GLclampf s, GLclampf t);
		void TexCoord2fv(glm::vec2 texcoord);

		void Tangent3f(GLfloat x, GLfloat y, GLfloat z);
		void Tangent3fv(glm::vec3 tangent);

		void Bitangent3f(GLfloat x, GLfloat y, GLfloat z);
		void Bitangent3fv(glm::vec3 bitangent);

		virtual void DrawArrays();
		virtual void DrawByIndex(GLuint index = 0);
		virtual void DrawByIndexs(uint32_t count);
		virtual void Draw() override;

		virtual void ShadowDraw() override;

	protected:
		bool mBatchDone;

	private:
		GLenum mPrimitiveType;
		GLuint mVerts;

		GLuint pVertCount;

		GLuint mVAO;

		GLuint mVertexArray;
		GLuint mNormalArray;
		GLuint mTexCoordsArray;
		GLuint mTangentArray;
		GLuint mBitangentArray;

		glm::vec3* pVerts;
		glm::vec3* pNorms;
		glm::vec2* pTexCoords;
		glm::vec3* pTangs;
		glm::vec3* pBitangs;
	};
}