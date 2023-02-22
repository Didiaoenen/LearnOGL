#pragma once

#include "Define.h"

#include <glm/glm.hpp>
#include <array>
#include <vector>

namespace ll
{

    class Device;
    class Camera;
    class Shadows;
    class DescriptorSet;
    class RenderPipeline;
    class DirectionalLight;

class PipelineUBO final
{
public:
    static void UpdateGlobalUBOView(const Camera* camera, std::array<float, UBOGlobal::COUNT>* bufferView);
    static void UpdateCameraUBOView(const RenderPipeline* pipeline, float* output, const Camera* camera);
    static void UpdateShadowUBOView(
        const RenderPipeline* pipeline, std::array<float, UBOShadow::COUNT>* shadowBufferView, std::array<float, UBOCSM::COUNT>* csmBufferView, const Camera* camera
    );
    static void UpdateShadowUBOLightView(
        const RenderPipeline* pipeline, std::array<float, UBOShadow::COUNT>* shadowBufferView, const Light* light, uint32_t level
    );
    static uint8_t GetCombineSignY();
    static void UpdatePlanarNormalAndDistance(const Shadows* shadowInfo, std::array<float, UBOShadow::COUNT>* shadowUBO);

    PipelineUBO() = default;
    ~PipelineUBO() = default;
    void Activate(Device* device, RenderPipeline* pipeline);
    void Destroy();
    void UpdateGlobalUBO(const Camera* camera);
    void UpdateCameraUBO(const Camera* camera);
    void UpdateMultiCameraUBO(const std::vector<Camera*>& cameras);
    void UpdateShadowUBO(const Camera* camera);
    void UpdateShadowUBOLight(DescriptorSet* globalDS, const Light* light, uint32_t level = 0U);
    void UpdateShadowUBORange(uint32_t offset, const glm::mat4* data);

    uint32_t GetCurrentCameraUBOOffset() const;
    void IncCameraUBOOffset();

private:
    static float GetPCFRadius(const Shadows* shadowInfo, const DirectionalLight* dirLight);
    void InitCombineSignY() const;

    RenderPipeline* _pipeline{ nullptr };
    Device* _device{ nullptr };
    Buffer* _cameraBuffer{ nullptr };

    uint32_t _currentCameraUBOOffset{ 0 };
    uint32_t _alignedCameraUBOSize{ 0 };

    bool _shadowUBOUpdated{ false };

    std::array<float, UBOGlobal::COUNT> _globalUBO;
    std::array<float, UBOShadow::COUNT> _shadowUBO;
    std::array<float, UBOCSM::COUNT> _csmUBO;

    std::vector<Buffer*> _ubos;
    std::vector<float> _cameraUBOs;

};

}