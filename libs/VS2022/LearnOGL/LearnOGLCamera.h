#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "LearnOGLDefine.h"

#include <vector>

namespace OGL
{
	class LearnOGLCamera
	{
	public:
		LearnOGLCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
		~LearnOGLCamera();

		void SetCameraPos(glm::vec3 position);
		void SetCameraInfo(CameraType type, const ProjInfo* info);

		void ProcessMouseMovement(double xoffset, double yoffset, bool constrainPitch = true);
		void ProcessMouseScroll(double yoffset);
		void ProcessKeyboard(CameraMovement dir, double dt);

	public:
		glm::vec3 mPosition;
		glm::vec3 mFront;
		glm::vec3 mUp;
		glm::vec3 mRight;
		glm::vec3 mWorldUp;

		float mYaw;
		float mPitch;
	
		float mZoom;
	
		float mMovementSpeed;
		float mMouseSenesitivity;

		CameraType mCameraType;
		PersProjInfo* mPersInfo;
		OrthoProjInfo* mOrthoInfo;

	private:
		void UpdateCameraVectors();

	};
}

