#pragma once

#include <glm/glm.hpp>

#include "LearnOGLDefine.h"
#include "LearnOGLCamera.h"

namespace OGL
{
	class LearnOGLPipeline
	{
	public:
		LearnOGLPipeline();
		~LearnOGLPipeline();


		void SetPos(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void SetRotate(float x, float y, float z);

		void SetCamera(LearnOGLCamera* camera);

		glm::mat4 GetTransform();
		glm::mat4 GetCameraView();
		glm::mat4 GetCameraProjection();

		glm::mat4 GetPerspectiveProjection(float fov, float aspect, float znear, float zfar);
		glm::mat4 GetOrthographicProjection(float left, float right, float top, float bottom, float znear, float zfar);

		glm::mat4 GetViewMatrix(glm::vec3 eye, glm::vec3 center, glm::vec3 up);

	private:
		glm::vec3 mPos;
		glm::vec3 mScale;
		glm::vec3 mRotate;

		LearnOGLCamera* mCamera;

		PersProjInfo* mPersInfo;
		OrthoProjInfo* mOrthoInfo;
	};
}