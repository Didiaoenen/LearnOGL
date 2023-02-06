#pragma once

#include <glm/glm.hpp>

#include "LearnOGLFBO.h"

#include <string>

namespace OGL
{
#define NUM_LAYERS 6

#define VERTEX_DATA     0
#define NORMAL_DATA     1
#define TEXTURE_DATA    2
#define INDEX_DATA      3

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
		glm::vec3 bitangent;
	};

	enum class VertAttrib
	{
		Position,
		Normal,
		TexCoord,
		Tangent,
		Bitangent,
	};

	enum class TexCoordIndex
	{
		TexCoord0x00,
		TexCoord0x01,
		TexCoord0x02,
		TexCoord0x03,
		TexCoord0x04,
	};

	enum class CameraMovement {
		Forward,
		Backward,
		Left,
		Right
	};

	struct DrawTex
	{
		uint32_t mIndex;
		LearnOGLFBO* mFBO;

		DrawTex(LearnOGLFBO* fbo, uint32_t index)
		{
			mFBO = fbo;
			mIndex = index;
		}
	};

	enum class DepthCompOpt
	{
		LESS = 0x0201,
		EQUAL,
		LEQUAL,
		GREATER,
		NOTEQUAL,
		GEQUAL,
	};

	struct CameraDirection
	{
		glm::vec3 mCenter;
		glm::vec3 mUp;
	};

	enum class AttachType
	{
		COLOR = 0x8CE0,
		DEPTH = 0x8D00,
		STENCIL = 0x8D20,
	};
}

