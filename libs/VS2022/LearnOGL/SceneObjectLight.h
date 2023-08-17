#pragma once

#include <glm/glm.hpp>

#include "SceneObjectBase.h"

#include "CBuffer.h"

namespace OGL
{
class SceneObjectLight : public SceneObjectBase
{
public:
    SceneObjectLight()
    {

    }

public:
    vec3 mUp{ 0.0f, 1.0f, 0.0f };
    vec2 mSize{ 0.0f, 0.0f };
    vec3 mPosition{ 0.0f, 0.0f, 0.0f };
    vec3 mDirection{ 0.0f, 0.0f, 1.0f };
    vec3 mColorDiffuse{ 1.0f, 1.0f, 1.0f };
    vec3 mColorSpecular{ 1.0f, 1.0f, 1.0f };
    vec3 mColorAmbient{ 1.0f, 1.0f, 1.0f };

    LightType mType{ UNDEFINED };
    float mAngleInnerCone{ glm::two_pi<float>() };
    float mAngleOuterCone{ glm::two_pi<float>() };
    float mAttenuationLinear{ 1.0f };
    float mAttenuationConstant{ 0.0f };
    float mAttenuationQuadratic{ 0.0f };
};
}

