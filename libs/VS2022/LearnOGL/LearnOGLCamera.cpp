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
		mCameraType = type;
		switch (mCameraType)
		{
			case OGL::CameraType::Perspective:
			{
				mPersInfo = (PersProjInfo*)info;
				mZoom = mPersInfo->fov;
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

	void LearnOGLCamera::ProcessMouseMovement(double xoffset, double yoffset, bool constrainPitch)
	{
		xoffset *= mMouseSenesitivity;
		yoffset *= mMouseSenesitivity;

		mYaw += xoffset;
		mPitch -= yoffset;

		if (constrainPitch)
		{
			if (mPitch > 89.0f)
			{
				mPitch = 89.0f;
			}
			if (mPitch < -89.0f)
			{
				mPitch = -89.0f;
			}
		}

		UpdateCameraVectors();
	}

	void LearnOGLCamera::ProcessMouseScroll(double yoffset)
	{
		mZoom -= yoffset;
		if (mZoom < 1.0f)
		{
			mZoom = 1.0f;
		}
		if (mZoom > 60.0f)
		{
			mZoom = 60.0f;
		}
	}

	void LearnOGLCamera::ProcessKeyboard(CameraMovement dir, double dt)
	{
		float velocity = mMovementSpeed * dt;
		switch (dir)
		{
		case OGL::CameraMovement::Forward:
			mPosition += mFront * velocity;
			break;
		case OGL::CameraMovement::Backward:
			mPosition -= mFront * velocity;
			break;
		case OGL::CameraMovement::Left:
			mPosition -= mRight * velocity;
			break;
		case OGL::CameraMovement::Right:
			mPosition += mRight * velocity;
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
