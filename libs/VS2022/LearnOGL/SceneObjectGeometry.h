
#pragma once

#include <vector>
#include <memory>

#include "SceneObjectBase.h"

#include "SceneObjectMesh.h"

using namespace std;

namespace OGL
{
class SceneObjectGeometry : public SceneObjectBase
{

public:

public:
	vector<shared_ptr<SceneObjectMesh>> mMeshs;
};
}