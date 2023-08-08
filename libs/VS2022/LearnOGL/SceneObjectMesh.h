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
    bool hasNormal{ false };
    bool hasVertexColors{ false };
    bool hasTextureCoords{ false };
    bool hasTangentsAndBitangents{ false };

    vector<_Vertex> mVertices;
    vector<uint32_t> mIndices;
};
}

