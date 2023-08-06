#include "PipelineStateManager.h"

using namespace OGL;
using namespace std;

PipelineStateManager::~PipelineStateManager()
{
}

bool PipelineStateManager::Initialize()
{
	PipelineState pipelineState;
	pipelineState.pipelineName = "";
	pipelineState.vertexShaderName = "";
	pipelineState.fragmentShaderName = "";
	pipelineState.bWriteDepth = true;
	pipelineState.depthTest = DepthTest::LEQUAL;
	pipelineState.stencilTest = StencilTest::NONE;
	pipelineState.cullFace = CullFace::BACK;
	pipelineState.sampleCount = mApp->GetConfiguration().msaaSamples;
	pipelineState.flag = DrawFlag::NONE;
	RegisterPipelineState(pipelineState);

	return true;
}

void PipelineStateManager::Finalize()
{
	Clear();
}

void PipelineStateManager::RegisterPipelineState(PipelineState& pipelineState)
{
	mPipelineStates.emplace(pipelineState.pipelineName, &pipelineState);
}

void PipelineStateManager::UnregisterPipelineState(PipelineState& pipelineState)
{
	mPipelineStates.erase(pipelineState.pipelineName);
}

void PipelineStateManager::Clear()
{
}

const shared_ptr<PipelineState> PipelineStateManager::GetPipelineState(string name) const
{
	const auto& it = mPipelineStates.find(name);
	if (it != mPipelineStates.end())
	{
		return it->second;
	}

	return nullptr;
}
