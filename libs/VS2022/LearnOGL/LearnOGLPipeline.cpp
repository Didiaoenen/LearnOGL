#include "LearnOGLPipeline.h"

namespace OGL
{
	LearnOGLPipeline::LearnOGLPipeline() :
		mPos(glm::vec3(0.0f)),
		mScale(glm::vec3(1.0f)),
		mRotate(glm::vec3(0.0f)),
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

	void LearnOGLPipeline::SetCamera(const LearnOGLCamera& camera)
	{
	}

	void LearnOGLPipeline::SetPerspectiveInfo(const PersProjInfo& info)
	{
		mPersInfo = info;
	}

	void LearnOGLPipeline::SetOrthographicInfo(const OrthoProjInfo& info)
	{
		mOrthoInfo = info;
	}

	glm::mat4 LearnOGLPipeline::GetPerspectiveProjection()
	{
		return glm::mat4();
	}

	glm::mat4 LearnOGLPipeline::GetOrthographicProjection()
	{
		return glm::mat4();
	}
}
