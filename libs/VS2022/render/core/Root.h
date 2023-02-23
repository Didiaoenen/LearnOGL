#pragma once

#include "../scene/Light.h"
#include "../scene/Model.h"
#include "../pipeline/RenderPipeline.h"
#include "../pipeline/RenderInterfaceTypes.h"

#include <tuple>
#include <string>
#include <vector>
#include <memory>
#include <cstdint>

namespace ll
{

class RenderPipelineBridge;

class Camera;
class Device;
class Pipeline;
class Batcher2d;
class Swapchain;
class RenderWindow;
class RenderPipeline;
class PipelineRuntime;
class IRenderWindowInfo;

class Root final
{
public:
    static Root* GetInstance();
    explicit Root(Device* device);
    ~Root();

    void Initialize(Swapchain* swapchain);
    void Destroy();

    void Resize(uint32_t width, uint32_t height);

    bool SetRenderPipeline(RenderPipeline* rppl = nullptr);
    void OnGlobalPipelineStateChanged();

    void ActiveWindow(RenderWindow* window);

    void ResetCumulativeTime();

    void FrameMove(float deltaTime, int32_t totalFrames);

    RenderWindow* CreateWindow(IRenderWindowInfo&);

    void DestroyWindow(RenderWindow*);

    void DestroyWindows();

    void DestroyScene(RenderScene* scene);

    void DestroyScenes();

    template <typename T, typename = std::enable_if_t<std::is_base_of<Model, T>::value>>
    T* CreateModel() 
    {
        T* model = new T();
        model->Initialize();
        return model;
    }

    void DestroyModel(Model* model);

    template <typename T, typename = std::enable_if_t<std::is_base_of<Light, T>::value>>
    T* CreateLight() 
    {
        T* light = new T();
        light->Initialize();
        return light;
    }

    void DestroyLight(Light* light);

    Camera* CreateCamera() const;
    inline Device* GetDevice() const { return _device; }
    inline void SetDevice(Device* device) { _device = device; }

    inline RenderWindow* GetMainWindow() const { return _mainWindow.get(); }

    inline void SetCurWindow(RenderWindow* window) { _curWindow = window; }

    inline RenderWindow* GetCurWindow() const { return _curWindow.get(); }

    void SetTempWindow(RenderWindow* window) { _tempWindow = window; }

    inline RenderWindow* GetTempWindow() const { return _tempWindow.get(); }

    inline const std::vector<IntrusivePtr<RenderWindow>>& GetWindows() const { return _windows; }

    inline bool UsesCustomPipeline() const { return _usesCustomPipeline; }

    inline PipelineRuntime* GetPipeline() const { return _pipelineRuntime.get(); }

    Pipeline* GetCustomPipeline() const;

    inline Batcher2d* GetBatcher2D() const { return _batcher; }

    inline const std::vector<IntrusivePtr<RenderScene>>& GetScenes() const { return _scenes; }

    inline float GetCumulativeTime() const { return _cumulativeTime; }

    inline float GetFrameTime() const { return _frameTime; }

    inline uint32_t GetFrameCount() const { return _frameCount; }

    inline uint32_t GetFps() const { return _fps; }

    void SetFixedFPS(uint32_t fps) { _fixedFPS = fps; }

    inline uint32_t GetFixedFPS() const { return _fixedFPS; }

    inline bool IsUsingDeferredPipeline() const { return _useDeferredPipeline; }

private:
    void FrameMoveBegin();
    void FrameMoveProcess(bool isNeedUpdateScene, int32_t totalFrames, const std::vector<IntrusivePtr<RenderWindow>>& windows);
    void FrameMoveEnd();

    Device* _device{ nullptr };
    Swapchain* _swapchain{ nullptr };
    Batcher2d* _batcher{ nullptr };
    IntrusivePtr<RenderWindow> _mainWindow;
    IntrusivePtr<RenderWindow> _curWindow;
    IntrusivePtr<RenderWindow> _tempWindow;
    std::vector<IntrusivePtr<RenderWindow>> _windows;
    IntrusivePtr<RenderPipeline> _pipeline{ nullptr };
    std::unique_ptr<PipelineRuntime> _pipelineRuntime;
    std::vector<IntrusivePtr<RenderScene>> _scenes;
    float _cumulativeTime{ 0.F };
    float _frameTime{ 0.F };
    float _fpsTime{ 0.F };
    uint32_t _frameCount{ 0 };
    uint32_t _fps{ 0 };
    uint32_t _fixedFPS{ 0 };
    bool _useDeferredPipeline{ false };
    bool _usesCustomPipeline{ false };

    std::vector<Camera*> _cameraList;
    std::vector<Swapchain*> _swapchains;
};

class RenderPipelineBridge final : public PipelineRuntime 
{
public:
    explicit RenderPipelineBridge(RenderPipeline* pipelineIn)
        : pipeline(pipelineIn) {}

    bool Activate(Swapchain* swapchain) override 
    {
        return pipeline->Activate(swapchain);
    }
    bool Destroy() noexcept override 
    {
        return pipeline->Destroy();
    }
    void Render(const std::vector<Camera*>& cameras) override 
    {
        pipeline->Render(cameras);
    }
    Device* GetDevice() const override 
    {
        return pipeline->GetDevice();
    }
    const MacroRecord& GetMacros() const override 
    {
        return pipeline->GetMacros();
    }
    GlobalDSManager* GetGlobalDSManager() const override 
    {
        return pipeline->GetGlobalDSManager();
    }
    DescriptorSetLayout* GetDescriptorSetLayout() const override 
    {
        return pipeline->GetDescriptorSetLayout();
    }
    DescriptorSet* GetDescriptorSet() const override 
    {
        return pipeline->GetDescriptorSet();
    }
    std::vector<CommandBuffer*> GetCommandBuffers() const override 
    {
        return pipeline->GetCommandBuffers();
    }
    PipelineSceneData* GetPipelineSceneData() const override 
    {
        return pipeline->GetPipelineSceneData();
    }
    const std::string& GetConstantMacros() const override 
    {
        return pipeline->GetConstantMacros();
    }
    Model* GetProfiler() const override 
    {
        return pipeline->GetProfiler();
    }
    void SetProfiler(Model* profiler) override 
    {
        pipeline->setProfiler(profiler);
    }
    GeometryRenderer* GetGeometryRenderer() const override 
    {
        return pipeline->GetGeometryRenderer();
    }
    float GetShadingScale() const override 
    {
        return pipeline->GetShadingScale();
    }
    void SetShadingScale(float scale) override 
    {
        pipeline->SetShadingScale(scale);
    }
    const std::string& GetMacroString(const std::string& name) const override 
    {
        static const std::string EMPTY_STRING;
        const auto& macros = pipeline->GetMacros();
        auto iter = macros.find(name);
        if (iter == macros.end()) 
        {
            return EMPTY_STRING;
        }
        return std::get<std::string>(iter->second);
    }
    int32_t GetMacroInt(const std::string& name) const override 
    {
        const auto& macros = pipeline->GetMacros();
        auto iter = macros.find(name);
        if (iter == macros.end()) 
        {
            return 0;
        }
        return std::get<int32_t>(iter->second);
    }
    bool GetMacroBool(const std::string& name) const override 
    {
        const auto& macros = pipeline->GetMacros();
        auto iter = macros.find(name);
        if (iter == macros.end()) 
        {
            return false;
        }
        return std::get<bool>(iter->second);
    }
    void SetMacroString(const std::string& name, const std::string& value) override 
    {
        pipeline->SetValue(name, value);
    }
    void SetMacroInt(const std::string& name, int32_t value) override 
    {
        pipeline->SetValue(name, value);
    }
    void SetMacroBool(const std::string& name, bool value) override 
    {
        pipeline->SetValue(name, value);
    }
    void OnGlobalPipelineStateChanged() override {
        pipeline->OnGlobalPipelineStateChanged();
    }
    void SetValue(const std::string& name, int32_t value) override 
    {
        pipeline->SetValue(name, value);
    }
    void SetValue(const std::string& name, bool value) override 
    {
        pipeline->SetValue(name, value);
    }
    bool IsOcclusionQueryEnabled() const override 
    {
        return pipeline->IsOcclusionQueryEnabled();
    }

    void ResetRenderQueue(bool reset) override 
    {
        pipeline->ResetRenderQueue(reset);
    }

    bool IsRenderQueueReset() const override 
    {
        return pipeline->IsRenderQueueReset();
    }

    RenderPipeline* pipeline = nullptr;
};

}