#pragma once

#include <string>

#include <glm/glm.hpp>

#include "BaseSceneObject.h"
#include "ParameterValueMap.h"

using namespace std;
using namespace glm;

namespace OGL
{
class SceneObjectMaterial : public BaseSceneObject
{
public:
	SceneObjectMaterial()
		: BaseSceneObject(0) 
	{
	}

	explicit SceneObjectMaterial(const char* name) 
		: SceneObjectMaterial() 
	{
		mName = name;
	}
	explicit SceneObjectMaterial(const string& name)
		: SceneObjectMaterial() 
	{
		mName = name;
	}
	explicit SceneObjectMaterial(string&& name) 
		: SceneObjectMaterial() 
	{
		mName = move(name);
	}

public:
	string mName;

	Color mDiffuse;
	Color mSpecular;
	Color mAmbient;
	Color mEmissive;
	Normal mNormal;

	Parameter mDiffuseIntensity;

	Parameter mSpecularPower;
	Parameter mSpecularIntensity;
};
}

