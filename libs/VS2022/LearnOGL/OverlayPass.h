#pragma once

#include "BaseDrawPass.h"

namespace OGL
{
class OverlayPass : public BaseDrawPass
{
public:
    OverlayPass(IGraphicsManager* pGfxMgr, IPipelineStateManager* pPipeMgr)
        : BaseDrawPass(pGfxMgr, pPipeMgr)
    {
        //mDrawSubPasses.push_back(std::make_shared<GuiSubPass>(mGraphicsManager, mPipelineStateManager));
        //mDrawSubPasses.push_back(std::make_shared<DebugOverlaySubPass>(mGraphicsManager, mPipelineStateManager));
    }
};
}

