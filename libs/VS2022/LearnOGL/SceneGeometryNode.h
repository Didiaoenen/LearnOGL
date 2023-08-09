#pragma once

#include "BaseSceneNode.h"

#include <vector>
#include <string>

using namespace std;

namespace OGL
{
class SceneGeometryNode : public SceneNode<SceneObjectGeometry>
{
public:
    using SceneNode::SceneNode;

    void AddMaterialRef(const string& key) { mMaterials.push_back(key); };

    string GetMaterialRef(const size_t index) 
    {
        if (index < mMaterials.size()) 
        {
            return mMaterials[index];
        }

        return string("default");
    }

public:
	vector<string> mMaterials;
};
}