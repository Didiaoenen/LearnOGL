#pragma once

#include <map>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "TreeNode.h"
#include "SceneObject.h"

using namespace std;
using namespace glm;

namespace OGL
{
class BaseSceneNode : public TreeNode
{
public:

	BaseSceneNode() 
	{
	};
	
	explicit BaseSceneNode(const string& name) 
	{
		mName = name;
	};

	[[nodiscard]] shared_ptr<mat4x4> GetCalculatedTransform() const
	{
		std::shared_ptr<mat4x4> result(new mat4x4());
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

	string mName;
	mat4x4 mRuntimeTransform;
	//std::vector<std::shared_ptr<SceneObjectTransform>> mTransforms;

};

template<typename T>
class SceneNode : public BaseSceneNode
{
public:
	using BaseSceneNode::BaseSceneNode;

	SceneNode() = default;

	void AddSceneObjectRef(const string& key) { mKeySceneObject = key; };

	const string& GetSceneObjectRef() { return mKeySceneObject; };

protected:
	string mKeySceneObject;

};
}