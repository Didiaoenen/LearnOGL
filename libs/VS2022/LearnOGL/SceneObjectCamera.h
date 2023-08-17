#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <assimp/scene.h>

#include "SceneObjectBase.h"

namespace OGL
{

enum class _CameraType 
{
    NONE,
    ORTHO,
    PERSPECTIVE,
};

class SceneObjectCamera : public SceneObjectBase
{
public:
    SceneObjectCamera()
    {
    }

    const glm::mat4& GetViewMatrix();
    const glm::mat4& GetProjectionMatrix();
    const glm::mat4& GetViewProjectionMatrix();

public:
    _CameraType mCameraType{ _CameraType::NONE };

    glm::mat4 mViewMatrix{ glm::identity<glm::mat4>() };
    glm::mat4 mProjectionMatrix{ glm::identity<glm::mat4>() };
    glm::mat4 mViewProjectionMatrix{ glm::identity<glm::mat4>() };

    glm::vec3 mUp{ 0.0f, 1.0f, 0.0f };
    glm::vec3 mLookAt{ 0.0f, 0.0f, -1.0f };
    glm::vec3 mPosition{ 0.0f, 0.0f, 0.0f };
    
    float mAspect{ 0.0f };
    float mHorizontalFOV{ 60.0f };
    float mOrthographicWidth{ 0.0f };
    float mOrthographicHeight{ 0.0f };
    float mClipPlaneNear{ 0.1f };
    float mClipPlaneFar{ 100.0f };
};

class SceneObjectOrthogonalCamera : public SceneObjectCamera 
{
public:
    using SceneObjectCamera::SceneObjectCamera;
};

class SceneObjectPerspectiveCamera : public SceneObjectCamera 
{
public:
    SceneObjectPerspectiveCamera()
    {
    }

    [[nodiscard]] float GetFov() const { return mFov; }

protected:
    float mFov;
};
}

