#pragma once

#include <string>

#include <glm/glm.hpp>

#include "SceneObjectBase.h"
#include "ParameterValueMap.h"

using namespace std;
using namespace glm;

namespace OGL
{
class SceneObjectMaterial : public SceneObjectBase
{
public:
	SceneObjectMaterial()
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

public:
	string mName;

	Color mDiffuse;
	Color mSpecular;
	Color mAmbient;
	Color mEmissive;
	Normal mNormal;
	Color mMask;

	Parameter mDiffuseIntensity;

	Parameter mSpecularPower;
	Parameter mSpecularIntensity;
};
}

