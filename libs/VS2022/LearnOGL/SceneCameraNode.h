#pragma once

#include <glm/glm.hpp>

#include "BaseSceneNode.h"

using namespace std;

namespace OGL
{
class SceneCameraNode : public SceneNode<SceneCameraNode>
{
public:
    using SceneNode::SceneNode;

    void SetTarget(const vec3& target) { mTarget = target; };
    const vec3& GetTarget() { return mTarget; };

    mat3x3 GetLocalAxis() override 
    {
        mat3x3 result;
        auto transform = GetCalculatedTransform();
        vec3 target = GetTarget();
        auto cameraPosition = vec3(0.0f);
        translate(*transform, cameraPosition);
        vec3 camera_z_axis({ 0.0f, 0.0f, 1.0f });
        vec3 camera_y_axis = target - cameraPosition;
        normalize(camera_y_axis);
        vec3 camera_x_axis;
        camera_x_axis = cross(camera_y_axis, camera_z_axis);
        camera_z_axis = cross(camera_x_axis, camera_y_axis);
        result[0] = camera_x_axis;
        result[1] = camera_y_axis;
        result[2] = camera_z_axis;

        return result;
    }

protected:
    vec3 mTarget{ 0.0f, 0.0f, -1.0f };
};
}