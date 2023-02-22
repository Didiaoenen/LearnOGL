#include "RenderPipeline.h"

#include "../base/Device.h"
#include "../scene/Camera.h"
#include "../scene/RenderWindow.h"

#include "RenderFlow.h"
#include "PipelineUBO.h"
#include "GlobalDSManager.h"
#include "PipelineSceneData.h"

ll::RenderPipeline* ll::RenderPipeline::GetInstance()
{
	return RenderPipeline::instance;
}

ll::Rect ll::RenderPipeline::GetRenderArea(Camera* camera)
{
	float w{ static_cast<float>(camera->GetWindow()->GetWidth()) };
	float h{ static_cast<float>(camera->GetWindow()->GetHeight()) };

	const auto& vp = camera->GetViewport();
	return 
	{
		static_cast<int32_t>(vp.x * w),
		static_cast<int32_t>(vp.y * h),
		static_cast<uint32_t>(vp.z * w),
		static_cast<uint32_t>(vp.w * h),
	};
}

ll::RenderPipeline::RenderPipeline()
	: _device(ll::Device::GetInstance())
{
	RenderPipeline::instance = this;

	_globalDSManager = new GlobalDSManager();
	_pipelineUBO = new PipelineUBO();
}

ll::RenderPipeline::~RenderPipeline()
{
}

bool ll::RenderPipeline::Activate(Swapchain* swapchain)
{
	_globalDSManager->Activate(_device);
	_descriptorSet = _globalDSManager->GetGlobalDescriptorSet();
	_pipelineUBO->Activate(_device, this);
	_pipelineSceneData->Activate(_device);

	GenerateConstantMacros();

	for (auto const& flow : _flows) 
	{
		flow->Activate(this);
	}

	return true;
}

bool ll::RenderPipeline::Destroy()
{
	return false;
}

bool ll::RenderPipeline::Initialize(const RenderPipelineInfo& info)
{
	_flows = info.flows;
	_tag = info.tag;
	return true;
}

void ll::RenderPipeline::Render(const std::vector<Camera*>& cameras)
{
	for (auto const& flow : _flows) 
	{
		for (auto* camera : cameras) 
		{
			flow->Render(camera);
		}
	}

	RenderPipeline::FramegraphGC();
}

void ll::RenderPipeline::OnGlobalPipelineStateChanged()
{
}



ll::DescriptorSetLayout * ll::RenderPipeline::GetDescriptorSetLayout() const
{
	return nullptr;
}

ll::RenderStage* ll::RenderPipeline::GetRenderstageByName(const std::string& name) const
{
	return nullptr;
}

bool ll::RenderPipeline::IsOccluded(const Camera* camera, const SubModel* subModel)
{
	return false;
}

bool ll::RenderPipeline::IsEnvmapEnabled() const
{
	return false;
}

ll::Viewport ll::RenderPipeline::GetViewport(Camera* camera)
{
	return Viewport();
}

ll::Rect ll::RenderPipeline::GetScissor(Camera* camera)
{
	return Rect();
}

void ll::RenderPipeline::GenQuadVertexData(const glm::vec4& viewport, float* data)
{
}

ll::Color ll::RenderPipeline::GetClearcolor(Camera* camera) const
{
	return Color();
}

ll::InputAssembler* ll::RenderPipeline::GetIAByRenderArea(const Rect& renderArea)
{
	return nullptr;
}

void ll::RenderPipeline::UpdateQuadVertexData(const glm::vec4& viewport, Buffer* buffer)
{
}

void ll::RenderPipeline::EnsureEnoughSize(const std::vector<Camera*>& cameras)
{
}

bool ll::RenderPipeline::OreateQuadInputAssembler(Buffer* quadIB, Buffer** quadVB, InputAssembler** quadIA)
{
	return false;
}

float ll::RenderPipeline::GetShadingScale() const
{
	return 0.0f;
}

void ll::RenderPipeline::SetShadingScale(float scale)
{
}

void ll::RenderPipeline::GenerateConstantMacros()
{
}

void ll::RenderPipeline::DestroyQuadInputAssembler()
{
}

void ll::RenderPipeline::FramegraphGC()
{
}
