#include "PipelineUBO.h"

void ll::PipelineUBO::UpdateGlobalUBOView(const Camera* camera, std::array<float, UBOGlobal::COUNT>* bufferView)
{
}

void ll::PipelineUBO::UpdateCameraUBOView(const RenderPipeline* pipeline, float* output, const Camera* camera)
{
}

void ll::PipelineUBO::UpdateShadowUBOView(const RenderPipeline* pipeline, std::array<float, UBOShadow::COUNT>* shadowBufferView, std::array<float, UBOCSM::COUNT>* csmBufferView, const Camera* camera)
{
}

void ll::PipelineUBO::UpdateShadowUBOLightView(const RenderPipeline* pipeline, std::array<float, UBOShadow::COUNT>* shadowBufferView, const Light* light, uint32_t level)
{
}

uint8_t ll::PipelineUBO::GetCombineSignY()
{
    return 0;
}

void ll::PipelineUBO::UpdatePlanarNormalAndDistance(const Shadows* shadowInfo, std::array<float, UBOShadow::COUNT>* shadowUBO)
{
}

void ll::PipelineUBO::Activate(Device* device, RenderPipeline* pipeline)
{
}

void ll::PipelineUBO::Destroy()
{
}

void ll::PipelineUBO::UpdateGlobalUBO(const Camera* camera)
{
}

void ll::PipelineUBO::UpdateCameraUBO(const Camera* camera)
{
}

void ll::PipelineUBO::UpdateMultiCameraUBO(const std::vector<Camera*>& cameras)
{
}

void ll::PipelineUBO::UpdateShadowUBO(const Camera* camera)
{
}

void ll::PipelineUBO::UpdateShadowUBOLight(DescriptorSet* globalDS, const Light* light, uint32_t level)
{
}

void ll::PipelineUBO::UpdateShadowUBORange(uint32_t offset, const glm::mat4* data)
{
}

uint32_t ll::PipelineUBO::GetCurrentCameraUBOOffset() const
{
    return 0;
}

void ll::PipelineUBO::IncCameraUBOOffset()
{
}

float ll::PipelineUBO::GetPCFRadius(const Shadows* shadowInfo, const DirectionalLight* dirLight)
{
    return 0.0f;
}

void ll::PipelineUBO::InitCombineSignY() const
{
}
