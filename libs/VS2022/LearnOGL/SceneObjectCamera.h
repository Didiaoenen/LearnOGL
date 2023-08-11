#pragma once

#include <glm/glm.hpp>

#include <assimp/scene.h>

#include "BaseSceneObject.h"

namespace OGL
{
class SceneObjectCamera : public BaseSceneObject 
{
public:
    SceneObjectCamera()
        : BaseSceneObject(0)
    {
    };

public:
    glm::vec3 mUp{ 0.0f, 1.0f, 0.0f };
    glm::vec3 mLookAt{ 0.0f, 0.0f, -1.0f };
    glm::vec3 mPosition{ 0.0f, 0.0f, 0.0f };
    
    float mAspect{ 0.0f };
    float mHorizontalFOV{ glm::radians(60.0f) };
    float mOrthographicWidth{ 0.0f };
    float mClipPlaneNear{ 1.0f };
    float mClipPlaneFar{ 100.0f };

};

class SceneObjectOrthogonalCamera : public SceneObjectCamera 
{
public:
    using SceneObjectCamera::SceneObjectCamera;
};

class SceneObjectPerspectiveCamera : public SceneObjectCamera 
{
protected:
    float mFov;

public:


public:
    explicit SceneObjectPerspectiveCamera()
    {
    }

    [[nodiscard]] float GetFov() const { return mFov; };
};
}

