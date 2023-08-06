#include "SkyBoxSubPass.h"

using namespace OGL;

void SkyBoxSubPass::Draw(Frame& frame)
{
	const auto& pipelineState = mPipelineStateManager->GetPipelineState("");
	if (pipelineState)
	{
		mGraphicsManager->SetPipelineState(pipelineState, frame);
		mGraphicsManager->DrawSkyBox(frame);
	}
}
