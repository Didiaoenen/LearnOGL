#include "Root.h"

#include "../base/Device.h"
#include "../base/Batcher2d.h"
#include "../base/Swapchain.h"
#include "../scene/Camera.h"
#include "../scene/RenderScene.h"
#include "../scene/RenderWindow.h"
#include "../pipeline/ForwardPipeline.h"
#include "../pipeline/DeferredPipeline.h"

#include <algorithm>

namespace ll
{
    Root* instance = nullptr;
}

ll::Root* ll::Root::GetInstance()
{
    return instance;
}

ll::Root::Root(Device* device)
    :_device(device)
{
    instance = this;

    _cameraList.reserve(6);
    _swapchains.reserve(2);
}

ll::Root::~Root()
{
}

void ll::Root::Initialize(Swapchain* swapchain)
{
    _swapchain = swapchain;

    RenderPassInfo renderPassInfo;

    ColorAttachment colorAttachment;
    //colorAttachment.format = swapchain->GetColorTexture()->GetFormat();
    //renderPassInfo.colorAttachments.emplace_back(colorAttachment);

    //auto& depthStencilAttachment = renderPassInfo.depthStencilAttachment;
    //depthStencilAttachment.format = swapchain->GetDepthStencilTexture()->GetFormat();
    //depthStencilAttachment.depthStoreOp = StoreOp::DISCARD;
    //depthStencilAttachment.stencilStoreOp = StoreOp::DISCARD;

    IRenderWindowInfo info;
    //info.title = std::string{ "rootMainWindow" };
    //info.width = swapchain->GetWidth();
    //info.height = swapchain->GetHeight();
    //info.renderPassInfo = renderPassInfo;
    //info.swapchain = swapchain;
    _mainWindow = CreateWindow(info);

    _curWindow = _mainWindow;

    //uint32_t maxJoints = (_device->GetCapabilities().maxVertexUniformVectors - 38) / 3;
    //maxJoints = maxJoints < 256 ? maxJoints : 256;
    //ll::LocalDescriptorSetLayoutResizeMaxJoints(maxJoints);
}

void ll::Root::Destroy()
{
}

void ll::Root::Resize(uint32_t width, uint32_t height)
{
    for (const auto& window : _windows) 
    {
        if (window->GetSwapchain()) 
        {
            window->Resize(width, height);
        }
    }
}

bool ll::Root::SetRenderPipeline(RenderPipeline* rppl)
{
    if (!_usesCustomPipeline) 
    {
        if (rppl != nullptr && dynamic_cast<DeferredPipeline*>(rppl) != nullptr) 
        {
            _useDeferredPipeline = true;
        }

        bool isCreateDefaultPipeline{ false };
        if (!rppl) 
        {
            rppl = new ForwardPipeline();
            rppl->Initialize({});
            isCreateDefaultPipeline = true;
        }

        _pipeline = rppl;
        _pipelineRuntime = std::make_unique<RenderPipelineBridge>(rppl);

        if (!_useDeferredPipeline || !_device->HasFeature(Feature::COMPUTE_SHADER)) 
        {
            _pipeline->SetClusterEnabled(false);
        }
        _pipeline->SetBloomEnabled(false);

        //if (!_pipeline->Activate(_mainWindow->GetSwapchain())) 
        //{
        //    if (isCreateDefaultPipeline) 
        //    {
        //    }

        //    _pipeline = nullptr;
        //    return false;
        //}
    }
    else 
    {

    }

    OnGlobalPipelineStateChanged();

    if (_batcher == nullptr) 
    {
        _batcher = new Batcher2d(this);
        if (!_batcher->Initialize()) 
        {
            Destroy();
            return false;
        }
    }

    return true;
}

void ll::Root::OnGlobalPipelineStateChanged()
{
    for (const auto& scene : _scenes) 
    {
        scene->OnGlobalPipelineStateChanged();
    }

    _pipelineRuntime->OnGlobalPipelineStateChanged();
}

void ll::Root::ActiveWindow(RenderWindow* window)
{
    _curWindow = window;
}

void ll::Root::ResetCumulativeTime()
{
    _cumulativeTime = 0;
}

void ll::Root::FrameMove(float deltaTime, int32_t totalFrames)
{
    for (const auto& scene : _scenes) 
    {
        scene->RemoveBatches();
    }

    if (_batcher != nullptr) 
    {
        _batcher->Update();
    }

    _cameraList.clear();
}

ll::RenderWindow* ll::Root::CreateWindow(IRenderWindowInfo&)
{
    return nullptr;
}

void ll::Root::DestroyWindow(RenderWindow*)
{
}

void ll::Root::DestroyWindows()
{
}

void ll::Root::DestroyScene(RenderScene*)
{
}

void ll::Root::DestroyScenes()
{
}

void ll::Root::DestroyModel(Model* model)
{
}

void ll::Root::DestroyLight(Light* light)
{
}

ll::Camera* ll::Root::CreateCamera() const
{
    return nullptr;
}

ll::Pipeline* ll::Root::GetCustomPipeline() const
{
    return dynamic_cast<ll::Pipeline*>(_pipelineRuntime.get());
}

void ll::Root::FrameMoveBegin()
{
}

void ll::Root::FrameMoveProcess(bool isNeedUpdateScene, int32_t totalFrames, const std::vector<IntrusivePtr<RenderWindow>>& windows)
{
    for (const auto& window : windows) 
    {
        window->ExtractRenderCameras(_cameraList);
    }

    if (_pipelineRuntime != nullptr && !_cameraList.empty()) 
    {
        _swapchains.clear();
        _swapchains.emplace_back(_swapchain);
        //_device->Acquire(_swapchains);
        uint32_t stamp = totalFrames;

        if (_batcher != nullptr) 
        {
            _batcher->UploadBuffers();
        }

        if (isNeedUpdateScene) 
        {
            for (const auto& scene : _scenes) 
            {
                scene->Update(stamp);
            }
        }
    }
}

void ll::Root::FrameMoveEnd()
{
    if (_pipelineRuntime != nullptr && !_cameraList.empty()) 
    {

        std::stable_sort(_cameraList.begin(), _cameraList.end(), [](const auto* a, const auto* b) 
        {
            return a->GetPriority() < b->GetPriority();
        });

#if CC_USE_GEOMETRY_RENDERER
        for (auto* camera : _cameraList) {
            if (camera->getGeometryRenderer()) {
                camera->getGeometryRenderer()->update();
            }
        }
#endif

        _pipelineRuntime->Render(_cameraList);
        
        _device->Present();
    }

    if (_batcher != nullptr) 
    {
        _batcher->Reset();
    }
}