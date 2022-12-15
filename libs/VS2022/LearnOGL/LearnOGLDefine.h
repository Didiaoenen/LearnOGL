#pragma once

#include <glm/glm.hpp>

#include <string>

namespace OGL
{
#define INVALID_UNIFORM_LOCATION 0xFFFFFFFF

	enum class CompileType
	{
		None,
		Vertex,
		Fragment,
		Geometry,
		Program,
	};

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

	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoords;
		glm::vec3 tangent;
		glm::vec3 bittangent;
	};

	enum class VertAttrib
	{
		Position,
		Normal,
		TexCoord,
		Tangent,
		BitTangent,
	};

	enum class TexCoordIndex
	{
		TexCoord0x00,
		TexCoord0x01,
		TexCoord0x02,
		TexCoord0x03,
	};
}

