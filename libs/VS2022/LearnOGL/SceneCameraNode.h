#pragma once

#include "BaseSceneNode.h"

namespace OGL
{
class SceneCameraNode : public SceneNode<SceneCameraNode>
{
public:
    void SetTarget(const glm::vec3& target) { mTarget = target; };
    const glm::vec3& GetTarget() { return mTarget; };

    glm::mat3x3 GetLocalAxis() override 
    {
        glm::mat3x3 result;
        auto pTransform = GetCalculatedTransform();
        glm::vec3 target = GetTarget();
        auto camera_position = glm::vec3(0.0f);
        glm::translate(*pTransform, camera_position);
        glm::vec3 camera_z_axis({ 0.0f, 0.0f, 1.0f });
        glm::vec3 camera_y_axis = target - camera_position;
        glm::normalize(camera_y_axis);
        glm::vec3 camera_x_axis;
        camera_x_axis = glm::cross(camera_y_axis, camera_z_axis);
        camera_z_axis = glm::cross(camera_x_axis, camera_y_axis);
        result[0] = camera_x_axis;
        result[1] = camera_y_axis;
        result[2] = camera_z_axis;

        return result;
    }

protected:
    glm::vec3 mTarget{ 0.0f, 0.0f, 0.0f };
};
}