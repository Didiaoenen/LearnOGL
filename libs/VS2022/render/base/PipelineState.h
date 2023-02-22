#pragma once
#include "Def_common.h"

namespace ll
{

class PipelineState
{
public:
    PipelineState();
    virtual ~PipelineState();

    void Initialize(const PipelineStateInfo& info);
    void Destroy();

    inline Shader* GetShader() const { return _shader; }
    inline PipelineBindPoint GetBindPoint() const { return _bindPoint; }
    inline PrimitiveMode GetPrimitive() const { return _primitive; }
    inline DynamicStateFlags GetDynamicStates() const { return _dynamicStates; }
    inline const InputState& GetInputState() const { return _inputState; }
    inline const RasterizerState& GetRasterizerState() const { return _rasterizerState; }
    inline const DepthStencilState& GetDepthStencilState() const { return _depthStencilState; }
    inline const BlendState& GetBlendState() const { return _blendState; }
    inline const RenderPass* GetRenderPass() const { return _renderPass; }
    inline const PipelineLayout* GetPipelineLayout() const { return _pipelineLayout; }

protected:
    virtual void DoInit(const PipelineStateInfo& info) = 0;
    virtual void DoDestroy() = 0;

    Shader* _shader = nullptr;
    PipelineBindPoint _bindPoint = PipelineBindPoint::GRAPHICS;
    PrimitiveMode _primitive = PrimitiveMode::TRIANGLE_LIST;
    DynamicStateFlags _dynamicStates = DynamicStateFlags::NONE;
    InputState _inputState;
    RasterizerState _rasterizerState;
    DepthStencilState _depthStencilState;
    BlendState _blendState;
    RenderPass* _renderPass = nullptr;
    uint32_t _subpass = 0U;
    PipelineLayout* _pipelineLayout = nullptr;
};

}