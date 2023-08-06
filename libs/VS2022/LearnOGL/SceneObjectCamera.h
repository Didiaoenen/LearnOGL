#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include <assimp/scene.h>

#include "BaseSceneObject.h"

namespace OGL
{
class SceneObjectCamera : public BaseSceneObject 
{
public:
    SceneObjectCamera()
        : BaseSceneObject(0), mAspect(16.0f / 9.0f)
    {
    };

    SceneObjectCamera(const aiCamera& camera)
    {

    }

public:

    [[nodiscard]] float GetNearClipDistance() const { return mNearClipDistance; };
    [[nodiscard]] float GetFarClipDistance() const { return mFarClipDistance; };

protected:
    float mAspect;
    float mNearClipDistance{ 1.0f };
    float mFarClipDistance{ 100.0f };

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
    explicit SceneObjectPerspectiveCamera(float fov = glm::pi<float>() / 2.0) : 
        mFov(fov) 
    {
    };

    [[nodiscard]] float GetFov() const { return mFov; };
};
}

