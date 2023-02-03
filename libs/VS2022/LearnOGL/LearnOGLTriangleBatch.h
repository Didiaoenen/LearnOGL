#pragma once

#include "LearnOGLBatch.h"
#include "LearnOGLMathExt.h"

namespace OGL
{
	class LearnOGLTriangleBatch : public OGL::LearnOGLBatch
	{
	public:
		LearnOGLTriangleBatch();
		~LearnOGLTriangleBatch();

		void BeginMesh(GLuint indexes);
		void AddTriangle(glm::vec3 verts[], glm::vec3 norms[], glm::vec2 texcoords[]);
		void End();

		virtual void Draw() override;

	private:
		GLushort* mIndexes{ nullptr };
		glm::vec3* mVerts{ nullptr };
		glm::vec3* mNorms{ nullptr };
		glm::vec2* mTexCoords{ nullptr };

		GLuint mMaxIndexes{ 0 };
		GLuint mNumIndexes{ 0 };
		GLuint mNumVerts{ 0 };

		GLuint mVAO{ 0 };
		GLuint mVBO[4];
	};
}
