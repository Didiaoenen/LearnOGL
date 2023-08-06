#include "GeometrySubPass.h"

#include "GraphicsManager.h"

using namespace OGL;

void GeometrySubPass::Draw(Frame& frame)
{
	const auto& pipelineState = mPipelineStateManager->GetPipelineState("");
	if (pipelineState)
	{
		mGraphicsManager->SetPipelineState(pipelineState, frame);
		mGraphicsManager->SetShadowMaps(frame);
		mGraphicsManager->DrawBatch(frame);
	}
}
