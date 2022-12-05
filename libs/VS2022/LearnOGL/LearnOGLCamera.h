#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace OGL
{
	class LearnOGLCamera
	{
	public:
		LearnOGLCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
		~LearnOGLCamera();

		glm::mat4 GetViewMatrix();

	public:
		glm::vec3 mPosition;
		glm::vec3 mFront;
		glm::vec3 mUp;
		glm::vec3 mRight;
		glm::vec3 mWorldUp;

		float mYaw;
		float mPitch;
	
		float mMovementSpeed;
		float mMouseSenesitivity;

		float mZoom;

	private:
		void UpdateCameraVectors();
	};
}

