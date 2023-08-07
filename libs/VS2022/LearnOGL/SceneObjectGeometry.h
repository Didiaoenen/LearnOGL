
#pragma once

#include <vector>
#include <memory>

#include "BaseSceneObject.h"

#include "SceneObjectMesh.h"

using namespace std;

namespace OGL
{
class SceneObjectGeometry : public BaseSceneObject
{

public:

public:
	vector<shared_ptr<SceneObjectMesh>> mMeshs;
};
}