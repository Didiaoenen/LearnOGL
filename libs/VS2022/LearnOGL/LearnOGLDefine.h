#pragma once

#include <glm/glm.hpp>

#include <string>

namespace OGL
{
	struct Transform
	{
		glm::vec3 pos;
		glm::vec3 scale;
		glm::vec3 rotation;
	};

	enum class CameraType
	{
		Perspective,
		Orthographic,
	};

	struct ProjInfo
	{

	};

	struct PersProjInfo : public ProjInfo
	{
		float fov;
		float width;
		float height;
		float zNear;
		float zFar;
	};

	struct OrthoProjInfo : public ProjInfo
	{
		float right;
		float left;
		float bottom;
		float top;
		float zNear;
		float zFar;
	};

	struct AppInfo
	{
		std::string title;
		int windowWidth;
		int windowHeight;
		int majorVersion;
		int minorVersion;
	};
}

