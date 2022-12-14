#include "LearnOGLCamera.h"

namespace OGL
{
	LearnOGLCamera::LearnOGLCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) :
		mFront(glm::vec3(0.0f, 0.0f, -1.0f)),
		mMovementSpeed(2.5f),
		mMouseSenesitivity(0.1f),
		mCameraType(CameraType::Perspective)
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

	void LearnOGLCamera::SetCameraInfo(CameraType type, const ProjInfo* info)
	{
		switch (type)
		{
			case OGL::CameraType::Perspective:
			{
				mPersInfo = (PersProjInfo*)info;
			}
			break;
			case OGL::CameraType::Orthographic:
			{
				mOrthoInfo = (OrthoProjInfo*)info;
			}
			break;
		default:
			break;
		}
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
