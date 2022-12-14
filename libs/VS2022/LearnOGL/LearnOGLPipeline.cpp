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
	}

	void LearnOGLPipeline::SetPerspectiveInfo(const PersProjInfo& info)
	{
		mPersInfo = info;
	}

	void LearnOGLPipeline::SetOrthographicInfo(const OrthoProjInfo& info)
	{
		mOrthoInfo = info;
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

	glm::mat4 LearnOGLPipeline::GetPerspectiveProjection()
	{
		return glm::perspective(glm::radians(mPersInfo.fov), mPersInfo.width / mPersInfo.height, mPersInfo.zNear, mPersInfo.zFar);
	}

	glm::mat4 LearnOGLPipeline::GetOrthographicProjection()
	{
		return glm::ortho(mOrthoInfo.left, mOrthoInfo.right, mOrthoInfo.bottom, mOrthoInfo.top, mOrthoInfo.zNear, mOrthoInfo.zFar);
	}
}
