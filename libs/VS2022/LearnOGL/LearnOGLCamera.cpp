#include "LearnOGLCamera.h"

namespace OGL
{
	LearnOGLCamera::LearnOGLCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
		:mFront(glm::vec3(0.0f, 0.0f, -1.0f)), mMovementSpeed(2.5f), mMouseSenesitivity(0.1f), mZoom(45.0f)
	{
		mPosition = position;
		mWorldUp = up;
		mYaw = yaw;
		mPitch = pitch;
		UpdateCameraVectors();
	}

	LearnOGLCamera::~LearnOGLCamera()
	{
	}

	glm::mat4 LearnOGLCamera::GetViewMatrix()
	{
		return glm::lookAt(mPosition, mPosition + mFront, mUp);
	}

	void LearnOGLCamera::UpdateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		front.y = sin(glm::radians(mPitch));
		front.z = sin(glm::radians(mYaw)) * cos(glm::radians(mPitch));
		mFront = glm::normalize(front);

		mRight = glm::normalize(glm::cross(mFront, mWorldUp));
		mUp = glm::normalize(glm::cross(mRight, mFront));
	}
}
