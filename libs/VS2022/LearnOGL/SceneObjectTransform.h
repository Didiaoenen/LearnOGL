#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "SceneObjectBase.h"

using namespace glm;

namespace OGL
{
class SceneObjectTransform : public SceneObjectBase
{
public:
    SceneObjectTransform()
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