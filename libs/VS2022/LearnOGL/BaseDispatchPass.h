#pragma once

#include "IDispatchPass.h"
#include "IGraphicsManager.h"

namespace OGL
{
class BaseDispatchPass : public IDispatchPass
{
public:
	BaseDispatchPass(IGraphicsManager* gfxManager, IPipelineStateManager* pipeManager)
		: mGraphicsManager(gfxManager), mPipelineStateManager(pipeManager)
	{}
		
	void BeginPass(Frame& frame) override;
	void EndPass(Frame& frame) override;

protected:
	IGraphicsManager* mGraphicsManager;
	IPipelineStateManager* mPipelineStateManager;
};
}