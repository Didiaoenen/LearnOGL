#pragma once

#include <vector>
#include <memory>

#include "IDrawPass.h"
#include "IDrawSubPass.h"
#include "IGraphicsManager.h"

using namespace std;

namespace OGL
{
class BaseDrawPass : public IDrawPass
{
public:
    BaseDrawPass(IGraphicsManager* gfxManager, IPipelineStateManager* pipeManager)
        : mGraphicsManager(gfxManager), mPipelineStateManager(pipeManager)
    {
    }

    void Draw(Frame& frame) override;

    void BeginPass(Frame& frame) override;
    void EndPass(Frame& frame) override;
        
    void EnableRenderToTexture() { mRenderToTexture = true; }
    void DisableRenderToTexture() { mRenderToTexture = false; }

protected:
    BaseDrawPass() = default;

protected:
    IGraphicsManager* mGraphicsManager;
    IPipelineStateManager* mPipelineStateManager;
    vector<shared_ptr<IDrawSubPass>> mDrawSubPasses;
    bool mRenderToTexture = false;
    bool mClearRT = false;
};
}

