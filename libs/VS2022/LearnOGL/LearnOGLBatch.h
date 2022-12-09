#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class LearnOGLBatch
{
public:
	LearnOGLBatch();
	virtual ~LearnOGLBatch();

	void Begin(GLenum primitive, GLuint nVerts, GLuint nTextureUnits = 0);

	void End();

	void CopyVertexData3f(glm::vec3* vertexs);
	void CopyNormalData3f(glm::vec3* normals);
	void CopyColorData4f(glm::vec3* colors);
	void CopyTexCoordData2f(glm::vec2* texcoords, GLuint uiTextureLayer);

	void Vertex3f(GLfloat x, GLfloat y, GLfloat z);
	void Vertex3fv(glm::vec3 vertex);

	void Normal3f(GLfloat x, GLfloat y, GLfloat z);
	void Normal3fv(glm::vec3 normal);

	void Color4f(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void Color4fv(glm::vec4 color);

	void MultiTexCoords2f(GLuint texture, GLclampf s, GLclampf t);
	void MultiTexCoords2fv(GLuint texture, glm::vec2);

	void Draw();

private:
	GLenum mPrimitiveType;

	GLuint mVAO;

	GLuint mVertexArray;
	GLuint mNormalArray;
	GLuint mColorArray;
	
	GLuint mVerts;

	glm::vec3* pVerts;
	glm::vec3* pNorms;
	glm::vec4* pColors;

	GLuint pVertCount;
};

