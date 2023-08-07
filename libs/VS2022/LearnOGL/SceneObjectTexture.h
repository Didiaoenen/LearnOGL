#pragma once

#include <string>

#include "BaseSceneObject.h"

using namespace std;

namespace OGL
{
class SceneObjectTexture : public BaseSceneObject
{
public:
    SceneObjectTexture()
        : BaseSceneObject(0) 
    {
    }

    explicit SceneObjectTexture(const string& name)
        : BaseSceneObject(0), mName(name)
    {
    }

public:
    string mName;
};
}

