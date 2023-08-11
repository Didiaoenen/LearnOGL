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

	[[nodiscard]] mat4 GetCalculatedTransform() const
	{
		auto result = glm::identity<mat4>();//* glm::mat4(mUnityAxis);
		for (auto it = mTransforms.rbegin(); it != mTransforms.rend(); it++)
		{
			result = result * (*it)->mMatrix;
		}

		return result * mRuntimeTransform;
	}

	virtual glm::mat3 GetLocalAxis() 
	{
		return glm::mat3 {
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
	}

	void AppendTransform(const char* key, const shared_ptr<SceneObjectTransform>& transform) 
	{
		mTransforms.push_back(transform);
	}

public:

	string mName;
	mat4 mRuntimeTransform{ glm::identity<mat4>() };
	vector<shared_ptr<SceneObjectTransform>> mTransforms;

	glm::mat3 mUnityAxis
	{
		{ 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f },
	};

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