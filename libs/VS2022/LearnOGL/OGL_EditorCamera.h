#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "LearnOGLDefine.h"

namespace OGL
{
struct CameraInfo
{
	float fov;
	float width;
	float height;
	float zNear;
	float zFar;
};

class OGL_EditorCamera final
{
public:
	OGL_EditorCamera();
	~OGL_EditorCamera() = default;

	void ProcessMouseMovement(double xoffset, double yoffset, bool constrainPitch = true);
	void ProcessMouseScroll(double yoffset);
	void ProcessKeyboard(CameraMovement dir, double dt);

public:
	glm::vec3 mPosition{ glm::vec3(0.0f, 0.0f, 0.0f) };
	glm::vec3 mUp{ glm::vec3(0.0f, 1.0f, 0.0f) };
	glm::vec3 mRight{ glm::vec3(1.0f, 0.0f, 0.0f) };
	glm::vec3 mFront{ glm::vec3(0.0f, 0.0f, -1.0f) };
	glm::vec3 mWorldUp{ glm::vec3(0.0f, 1.0f, 0.0f) };

	float mYaw{ -90.0f };
	float mPitch{ 0.0f };

	float mZoom{ 0.0f };

	float mMovementSpeed{ 2.5f };
	float mMouseSenesitivity{ 0.1f };

	CameraInfo mCameraInfo{};

private:
	void UpdateCameraVectors();

};
}

