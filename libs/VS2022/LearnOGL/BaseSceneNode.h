#pragma once

#include <map>
#include <string>
#include <vector>
#include <glm/ext.hpp>

#include "TreeNode.h"
#include "SceneObject.h"

namespace OGL
{
class BaseSceneNode : public TreeNode
{
public:

	[[nodiscard]] std::shared_ptr<glm::mat4x4> GetCalculatedTransform() const
	{
		std::shared_ptr<glm::mat4x4> result(new glm::mat4x4());
		//for (auto it = mTransforms.rbegin(); it != mTransforms.rend(); it++)
		//{
		//	*result = *result * static_cast<glm::mat4x4>(**it);
		//}

		//*result = *result * mRuntimeTransform;

		return result;
	}

	virtual glm::mat3x3 GetLocalAxis() 
	{
		return glm::mat3x3 {
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f }
		};
	}
protected:
	glm::mat4x4 mRuntimeTransform;
	//std::vector<std::shared_ptr<SceneObjectTransform>> mTransforms;

};

template<typename T>
class SceneNode : public BaseSceneNode
{
public:
	SceneNode() = default;

	void AddSceneObjectRef(const std::string& key) { mKeySceneObject = key; };

	const std::string& GetSceneObjectRef() { return mKeySceneObject; };



protected:
	std::string mKeySceneObject;

};
}