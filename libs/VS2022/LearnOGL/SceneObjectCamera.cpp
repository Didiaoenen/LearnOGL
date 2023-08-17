#include "SceneObjectCamera.h"

using namespace OGL;

const glm::mat4& OGL::SceneObjectCamera::GetViewMatrix()
{
	return glm::mat4(1.0);
}

const glm::mat4& SceneObjectCamera::GetProjectionMatrix()
{
	if (mCameraType == _CameraType::ORTHO)
	{
		auto width = mOrthographicWidth / 2;
		auto height = mOrthographicHeight / 2;
		mProjectionMatrix = glm::ortho(-width, width, -height, height, mClipPlaneNear, mClipPlaneFar);
	}
	else if (mCameraType == _CameraType::PERSPECTIVE)
	{
		mProjectionMatrix = glm::perspective(glm::radians(mHorizontalFOV), mOrthographicWidth / mOrthographicHeight, mClipPlaneNear, mClipPlaneFar);
	}
	return mProjectionMatrix;
}

const glm::mat4& SceneObjectCamera::GetViewProjectionMatrix()
{
	return glm::mat4(1.0);
}
