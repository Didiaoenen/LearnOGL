#pragma once

#include "IDrawSubPass.h"
#include "IGraphicsManager.h"
#include "IPipelineStateManager.h"

namespace OGL
{
class BaseSubPass : public IDrawSubPass
{
public:
	BaseSubPass(IGraphicsManager* gfxManager, IPipelineStateManager* pipeManager)
		:mGraphicsManager(gfxManager), mPipelineStateManager(pipeManager)
	{
	}

	virtual void BeginSubPass() override;
	virtual void EndSubPass() override;

protected:
	IGraphicsManager* mGraphicsManager;
	IPipelineStateManager* mPipelineStateManager;
};
}