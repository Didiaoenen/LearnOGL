#pragma once

#include "BaseDrawPass.h"

namespace OGL
{
class ForwardGeometryPass : public BaseDrawPass
{
public:
    ForwardGeometryPass(IGraphicsManager* gfxManger, IPipelineStateManager* pipeManager);
};
}

