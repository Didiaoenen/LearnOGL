#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "BaseSceneObject.h"

using namespace glm;

namespace OGL
{
class SceneObjectTransform : public BaseSceneObject
{
public:
    SceneObjectTransform()
        : BaseSceneObject(0) 
    {
    }

    explicit SceneObjectTransform(const mat4& matrix)
        : SceneObjectTransform() 
    {
        mMatrix = matrix;
    }

public:
    mat4 mMatrix{ glm::identity<mat4>() };
};
}