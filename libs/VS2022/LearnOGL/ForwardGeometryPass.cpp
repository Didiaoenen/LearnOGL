#include "ForwardGeometryPass.h"

#include "SkyBoxSubPass.h"
#include "GeometrySubPass.h"

using namespace OGL;
using namespace std;

ForwardGeometryPass::ForwardGeometryPass(IGraphicsManager* gfxManager, IPipelineStateManager* pipeManager)
    : BaseDrawPass(gfxManager, pipeManager)
{
    mClearRT = true;
    mDrawSubPasses.push_back(make_shared<SkyBoxSubPass>(mGraphicsManager, mPipelineStateManager));
    mDrawSubPasses.push_back(make_shared<GeometrySubPass>(mGraphicsManager, mPipelineStateManager));
}