#pragma once

#include <string>

namespace OGL
{
struct GfxConfiguration
{
	explicit GfxConfiguration()
	{

	}

	uint32_t screenWidth{ 960 };
	uint32_t screenHeight{ 720 };

	uint32_t msaaSamples{ 4 };

	static const uint32_t kMaxInFlightFrameCount{2};
	static const uint32_t kMaxShadowMapCount{8};

	static const uint32_t kShadowMapWidth = 512;
	static const uint32_t kShadowMapHeight = 512;

	bool fixOpenGLPerspectiveMatrix = false;
};
}
