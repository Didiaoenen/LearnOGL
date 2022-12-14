#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../LearnOGL/LearnOGLModel.h"

#include <iostream>
#include <vector>

namespace OGL
{
	enum class oglBatchAttrib
	{
		Position = 0,
		Normal,
		TexCoord,
	};

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
		void CopyTexCoordData2f(glm::vec2* texcoord);

		void Vertex3f(GLfloat x, GLfloat y, GLfloat z);
		void Vertex3fv(glm::vec3 vertex);

		void Normal3f(GLfloat x, GLfloat y, GLfloat z);
		void Normal3fv(glm::vec3 normal);

		void TexCoord2f(GLclampf s, GLclampf t);
		void TexCoord2fv(glm::vec2 texcoord);

		virtual void Draw() override;

	private:
		GLenum mPrimitiveType;
		GLuint mVerts;
		bool mBatchDone;

		GLuint pVertCount;

		GLuint mVAO;

		GLuint mVertexArray;
		GLuint mNormalArray;
		GLuint mTexCoordArray;

		glm::vec3* pVerts;
		glm::vec3* pNorms;
		glm::vec2* pTexCoord;
	};
}