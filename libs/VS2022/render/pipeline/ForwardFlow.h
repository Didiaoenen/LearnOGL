#pragma once

#include "RenderFlow.h"

namespace ll
{

class ForwardFlow : public RenderFlow
{
public:
    static const RenderFlowInfo& GetInitializeInfo();

    ForwardFlow() = default;
    ~ForwardFlow() override;

    bool Initialize(const RenderFlowInfo& info) override;
    void Activate(RenderPipeline* pipeline) override;
    void Destroy() override;
    void Render(Camera* camera) override;

private:
    static RenderFlowInfo initInfo;
};

}