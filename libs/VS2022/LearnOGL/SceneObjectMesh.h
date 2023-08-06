#pragma once

#include <vector>

#include "BaseSceneObject.h"

#include "CBuffer.h"

using namespace std;

namespace OGL
{
class SceneObjectMesh : public BaseSceneObject
{
public:
    SceneObjectMesh() {}
    ~SceneObjectMesh() {}

public:
    vector<_Vertex> mVertices;
    vector<uint32_t> mIndices;
};
}

