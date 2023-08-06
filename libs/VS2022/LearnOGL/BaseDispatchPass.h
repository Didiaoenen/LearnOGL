#pragma once

#include "IDispatchPass.h"
#include "IGraphicsManager.h"

namespace OGL
{
class BaseDispatchPass : public IDispatchPass
{
public:
	BaseDispatchPass(IGraphicsManager* pGfxMgr, IPipelineStateManager* pPipeMgr)
		: mGraphicsManager(pGfxMgr), mPipelineStateManager(pPipeMgr)
	{}
		
	void BeginPass(Frame& frame) override;
	void EndPass(Frame& frame) override;

protected:
	IGraphicsManager* mGraphicsManager;
	IPipelineStateManager* mPipelineStateManager;
};
}