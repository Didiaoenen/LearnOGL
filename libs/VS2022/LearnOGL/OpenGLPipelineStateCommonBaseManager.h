#pragma once

#include <stdint.h>

#include "PipelineStateManager.h"

namespace OGL
{
struct OpenGLPipelineState : public PipelineState
{
	uint32_t shaderProgram = 0;
	OpenGLPipelineState(PipelineState& rhs) : PipelineState(rhs) {}
	OpenGLPipelineState(PipelineState&& rhs) : PipelineState(std::move(rhs)) {}
};

class OpenGLPipelineStateCommonBaseManager : public PipelineStateManager 
{
public:
	using PipelineStateManager::PipelineStateManager;
	virtual ~OpenGLPipelineStateCommonBaseManager() = default;

protected:
	bool InitializePipelineState(PipelineState** pipelineState) final;
	void DestroyPipelineState(PipelineState& pipelineState) final;
};
}

