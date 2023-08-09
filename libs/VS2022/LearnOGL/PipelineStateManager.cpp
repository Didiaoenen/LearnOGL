#include "PipelineStateManager.h"

using namespace OGL;
using namespace std;

#define VS_BASIC_SOURCE_FILE "basic.vert"
#define PS_BASIC_SOURCE_FILE "basic.frag"

PipelineStateManager::~PipelineStateManager()
{
}

bool PipelineStateManager::Initialize()
{
	PipelineState pipelineState;
	pipelineState.pipelineName = "BASIC";
	pipelineState.vertexShaderName = VS_BASIC_SOURCE_FILE;
	pipelineState.fragmentShaderName = PS_BASIC_SOURCE_FILE;
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
	mPipelineStates.emplace(pipelineState.pipelineName, make_shared<PipelineState>(pipelineState));
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
