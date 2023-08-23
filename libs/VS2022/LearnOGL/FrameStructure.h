#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "Scene.h"
#include "CBuffer.h"

#include "OGL_Base.h"
#include "OGL_Entity.h"

namespace OGL
{
struct DrawFrameContext : PerFrameConstants, FrameTextures
{

};

struct DrawBatchContext : PerBatchConstants
{
	virtual ~DrawBatchContext() = default;

	int32_t batchIndex{ 0 };
	MaterialTexture material;
	Ref<OGL_Entity> entity;
};

struct Frame : GlobalTexture
{
	int32_t frameIndex{ 0 };
	DrawFrameContext frameContext;
	std::vector<std::shared_ptr<DrawBatchContext>> batchContexts;
	LightInfo lightInfo;
	glm::vec4 clearColor {0.2f, 0.3f, 0.4f, 1.0f};
	std::vector<Texture2D> colorTextures;
	Texture2D depthTexture;
	intptr_t frameBuffer;
	bool renderToTexture = false;
	bool enableMSAA = false;
	bool clearRT = true;
};
}
