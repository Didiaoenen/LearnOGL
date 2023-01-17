#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "LearnOGLFBO.h"
#include "LearnOGLDepthFBO.h"
#include "LearnOGLCubeMapFBO.h"
#include "LearnOGLHDRFBO.h"

#include <map>
#include <string>

namespace OGL
{
	class LearnOGLCommand
	{
	public:
		LearnOGLCommand();
		LearnOGLCommand(std::string name);
		~LearnOGLCommand();

		void GetTemporaryRT(GLuint id, GLuint width, GLuint height);
		void GetTemporaryHDRRT(GLuint id, GLuint width, GLuint height);
		void GetTemporaryCubeMapRT(GLuint id, GLuint width, GLuint height);
		void ClearRenderTarget(bool depth, bool color, glm::vec4 backgroundcolor);

		void SetRenderTarget(GLuint id);

		void SetGloablInt(GLuint id, GLint value);
		void SetGloablIntArray(GLuint id, GLint* value);

		void SetGloablFloat(GLuint id, GLfloat value);
		void SetGloablFloatArray(GLuint id, GLfloat* value);

		void SetGlobalVector(GLuint id, glm::vec4 vec);
		void SetGlobalVectorArray(GLuint id, glm::vec4* vec);

		void SetGlobalMatrix(GLuint id, glm::mat4 vec);
		void SetGlobalMatrixArray(GLuint id, glm::mat4* vec);

		void SetViewport(GLfloat beginX, GLfloat beginY, GLfloat width, GLfloat height);

		void EnableCullFace(bool face);

		void ReleaseTemporaryRT(GLuint id);

		void Clear();

	public:
		std::string mName;

		bool mDepthBit{ false };
		bool mColorBit{ false };

		glm::vec4 mBackgroundColor = glm::vec4(0.0f);

		std::map<GLuint, LearnOGLFBO*> mUintTexMap;
	
	private:

	};
}