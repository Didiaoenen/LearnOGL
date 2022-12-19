#include "LearnOGLPipeline.h"

namespace OGL
{
	LearnOGLPipeline::LearnOGLPipeline() :
		mPos(glm::vec3(0.0f)),
		mScale(glm::vec3(1.0f)),
		mRotate(glm::vec3(0.0f)),
		mCamera(nullptr),
		mPersInfo(),
		mOrthoInfo()
	{

	}

	LearnOGLPipeline::~LearnOGLPipeline()
	{
	}

	void LearnOGLPipeline::SetPos(float x, float y, float z)
	{
		mPos.x = x;
		mPos.y = y;
		mPos.z = z;
	}

	void LearnOGLPipeline::SetScale(float x, float y, float z)
	{
		mScale.x = x;
		mScale.y = y;
		mScale.z = z;
	}

	void LearnOGLPipeline::SetRotate(float x, float y, float z)
	{
		mRotate.x = x;
		mRotate.y = y;
		mRotate.z = z;
	}

	void LearnOGLPipeline::SetCamera(LearnOGLCamera* camera)
	{
		mCamera = camera;
		mPersInfo = mCamera->mPersInfo;
		mOrthoInfo = mCamera->mOrthoInfo;
	}

	glm::mat4 LearnOGLPipeline::GetTransform()
	{
		glm::mat4 transform = glm::mat4(1.0);
		transform = glm::scale(transform, mScale);
		transform = glm::translate(transform, mPos);
		transform = glm::rotate(transform, glm::radians(mRotate.x), glm::vec3(1.0, 0.0, 0.0));
		transform = glm::rotate(transform, glm::radians(mRotate.y), glm::vec3(0.0, 1.0, 0.0));
		transform = glm::rotate(transform, glm::radians(mRotate.z), glm::vec3(0.0, 0.0, 1.0));
		return transform;
	}

	glm::mat4 LearnOGLPipeline::GetCameraView()
	{
		return glm::lookAt(mCamera->mPosition, mCamera->mPosition + mCamera->mFront, mCamera->mUp);
	}

	glm::mat4 LearnOGLPipeline::GetCameraProjection()
	{
		if (mCamera->mCameraType == CameraType::Perspective)
		{
			return glm::perspective(glm::radians(mPersInfo->fov), mPersInfo->width / mPersInfo->height, mPersInfo->zNear, mPersInfo->zFar);
		}
		else if (mCamera && mCamera->mCameraType == CameraType::Orthographic)
		{
			return glm::ortho(mOrthoInfo->left, mOrthoInfo->right, mOrthoInfo->bottom, mOrthoInfo->top, mOrthoInfo->zNear, mOrthoInfo->zFar);
		}
	}

	glm::mat4 LearnOGLPipeline::GetPerspectiveProjection(float fov, float aspect, float znear, float zfar)
	{
		return glm::perspective(glm::radians(fov), aspect, znear, zfar);
	}

	glm::mat4 LearnOGLPipeline::GetOrthographicProjection(float left, float right, float top, float bottom, float znear, float zfar)
	{
		return glm::ortho(left, right, top, bottom, znear, zfar);
	}

	glm::mat4 LearnOGLPipeline::GetViewMatrix(glm::vec3 eye, glm::vec3 center, glm::vec3 up)
	{
		return glm::lookAt(eye, center, up);
	}

}
