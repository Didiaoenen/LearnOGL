#include "BaseDrawPass.h"

using namespace OGL;

void BaseDrawPass::Draw(Frame& frame)
{
	for (const auto& subPass : mDrawSubPasses)
	{
		subPass->BeginSubPass();
		subPass->Draw(frame);
		subPass->EndSubPass();
	}
}

void BaseDrawPass::BeginPass(Frame& frame)
{
	frame.renderToTexture = mRenderToTexture;
	frame.clearRT = mClearRT;

	mGraphicsManager->BeginPass(frame);
}

void BaseDrawPass::EndPass(Frame& frame)
{
	mGraphicsManager->EndPass(frame);
}
