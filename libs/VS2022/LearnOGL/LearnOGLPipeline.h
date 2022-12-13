#pragma once

#include <glm/glm.hpp>

#include "LearnOGLApp.h"
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

		void SetCamera(const LearnOGLCamera& camera);
		void SetPerspectiveInfo(const PersProjInfo& info);
		void SetOrthographicInfo(const OrthoProjInfo& info);

		glm::mat4 GetPerspectiveProjection();
		glm::mat4 GetOrthographicProjection();

	private:
		glm::vec3 mPos;
		glm::vec3 mScale;
		glm::vec3 mRotate;

		LearnOGLCamera mCamera;

		PersProjInfo mPersInfo;
		OrthoProjInfo mOrthoInfo;
	};
}