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
		Color,
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
		void CopyColorData4f(glm::vec4* colors);
		void CopyNormalData3f(glm::vec3* normals);
		void CopyTexCoordData2f(glm::vec2* texcoord);

		void Vertex3f(GLfloat x, GLfloat y, GLfloat z);
		void Vertex3fv(glm::vec3 vertex);

		void Color4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
		void Color4fv(glm::vec4 color);

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
		GLuint mColorArray;
		GLuint mNormalArray;
		GLuint mTexCoordArray;

		glm::vec3* pVerts;
		glm::vec4* pColors;
		glm::vec3* pNorms;
		glm::vec2* pTexCoord;
	};
}