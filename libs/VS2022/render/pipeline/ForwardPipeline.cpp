#include "ForwardPipeline.h"

#include "../base/Queue.h"
#include "../base/Buffer.h"
#include "../base/Device.h"
#include "../base/Swapchain.h"
#include "../base/DescriptorSet.h"
#include "../pipeline/Utils.h"
#include "../pipeline/RenderFlow.h"
#include "../pipeline/ShadowFlow.h"
#include "../pipeline/ForwardFlow.h"
#include "../pipeline/PipelineUBO.h"
#include "../pipeline/SceneCulling.h"
#include "../pipeline/GlobalDSManager.h"
#include "../pipeline/PipelineSceneData.h"
#include "../gl/glCommandBuffer.h"
#include "../scene/Camera.h"

namespace ll
{
    std::string ForwardPipeline::fgStrHandleForwardPass = "forwardPass";
}

ll::ForwardPipeline::ForwardPipeline()
{
    _pipelineSceneData = new PipelineSceneData();
}

bool ll::ForwardPipeline::Initialize(const RenderPipelineInfo& info)
{
    RenderPipeline::Initialize(info);

    if (_flows.empty()) 
    {
        auto* shadowFlow = new ShadowFlow;
        shadowFlow->Initialize(ShadowFlow::GetInitializeInfo());
        _flows.emplace_back(shadowFlow);

        auto* forwardFlow = new ForwardFlow;
        forwardFlow->Initialize(ForwardFlow::GetInitializeInfo());
        _flows.emplace_back(forwardFlow);
    }

    return true;
}

bool ll::ForwardPipeline::Destroy()
{
	return false;
}

bool ll::ForwardPipeline::Activate(Swapchain* swapchain)
{
    _macros["CC_PIPELINE_TYPE"] = 0;

    if (!RenderPipeline::Activate(swapchain)) 
    {
        return false;
    }

    if (!ActiveRenderer(swapchain)) 
    {
        return false;
    }

    return true;
}

void ll::ForwardPipeline::Render(const std::vector<Camera*>& cameras)
{
    auto* device = ll::Device::GetInstance();
    const bool enableOcclusionQuery = IsOcclusionQueryEnabled();
    if (enableOcclusionQuery) 
    {
        device->GetQueryPoolResults(_queryPools[0]);
    }

    _commandBuffers[0]->Begin();

    if (enableOcclusionQuery) 
    {
        _commandBuffers[0]->ResetQueryPool(_queryPools[0]);
    }

    _pipelineUBO->UpdateGlobalUBO(cameras[0]);
    _pipelineUBO->UpdateMultiCameraUBO(cameras);
    EnsureEnoughSize(cameras);
    DecideProfilerCamera(cameras);

    for (auto* camera : cameras) 
    {
        bool isCullingEnable = camera->IsCullingEnabled();
        if (isCullingEnable) 
        {
            ValidPunctualLightsCulling(this, camera);
            SceneCulling(this, camera);
        }
        for (auto const& flow : _flows) 
        {
            flow->Render(camera);
        }
        //_fg.Compile();
        //_fg.Execute();
        //_fg.Reset();
        _pipelineUBO->IncCameraUBOOffset();
    }

    if (enableOcclusionQuery) 
    {
        _commandBuffers[0]->CompleteQueryPool(_queryPools[0]);
    }

    _commandBuffers[0]->End();
    _device->FlushCommands(_commandBuffers);
    _device->GetQueue()->Submit(_commandBuffers);

    RenderPipeline::FramegraphGC();
}

bool ll::ForwardPipeline::ActiveRenderer(Swapchain* swapchain)
{
    _commandBuffers.push_back(_device->GetCommandBuffer());
    _queryPools.push_back(_device->GetQueryPool());

    Sampler* const sampler = GetGlobalDSManager()->GetPointSampler();

    _descriptorSet->BindSampler(SHADOWMAP::BINDING, sampler);
    _descriptorSet->BindSampler(SPOTSHADOWMAP::BINDING, sampler);
    _descriptorSet->Update();

    _macros["CC_USE_HDR"] = static_cast<bool>(_pipelineSceneData->IsHDR());
    _macros["CC_SUPPORT_FLOAT_TEXTURE"] = hasAnyFlags(_device->GetFormatFeatures(Format::RGBA32F), FormatFeature::RENDER_TARGET | FormatFeature::SAMPLED_TEXTURE);
    _macros["CC_USE_DEBUG_VIEW"] = static_cast<int32_t>(0);

    uint32_t ibStride = 4;
    uint32_t ibSize = ibStride * 6;
    if (_quadIB == nullptr) 
    {
        _quadIB = _device->CreateBuffer(
            { BufferUsageBit::INDEX | BufferUsageBit::TRANSFER_DST, MemoryUsageBit::DEVICE, ibSize, ibStride }
        );
    }

    if (_quadIB == nullptr) 
    {
        return false;
    }

    uint32_t ibData[] = { 0, 1, 2, 1, 3, 2 };
    _quadIB->Update(ibData, sizeof(ibData));

    _width = swapchain->GetWidth();
    _height = swapchain->GetHeight();
    return true;
}