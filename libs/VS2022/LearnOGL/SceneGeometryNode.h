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
    void AddMaterialRef(const string& key) { mMaterials.push_back(key); };

    string GetMaterialRef(const size_t index) 
    {
        if (index < mMaterials.size()) 
        {
            return mMaterials[index];
        }

        return std::string("default");
    }

public:
	vector<string> mMaterials;
};
}