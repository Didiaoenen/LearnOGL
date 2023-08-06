#pragma once

#include <string>
#include <memory>

#include "CBuffer.h"
#include "IRuntimeModule.h"

using namespace std;

namespace OGL
{
struct PipelineState
{
	virtual ~PipelineState() = default;

	string pipelineName;

	string vertexShaderName;
	string fragmentShaderName;
	string geometryShaderName;

	CullFace cullFace{ CullFace::BACK };
	DepthTest depthTest{ DepthTest::ALWAYS };
	StencilTest stencilTest{ StencilTest::NONE };
	PixelFormat pixelFormat{ PixelFormat::RGBA8 };
	uint32_t sampleCount{ 1 };
	
	bool bWriteDepth{ true };

	DrawFlag flag;
};

class IPipelineStateManager : public IRuntimeModule
{
public:
	virtual void RegisterPipelineState(PipelineState& pipelineState) = 0;
	virtual void UnregisterPipelineState(PipelineState& pipelineState) = 0;
	virtual void Clear() = 0;

	[[nodiscard]] virtual const std::shared_ptr<PipelineState> GetPipelineState(std::string name) const = 0;
};
}