#include "RenderScene.h"

ll::RenderScene::RenderScene()
{
}

ll::RenderScene::~RenderScene()
{
}

bool ll::RenderScene::Initialize(const IRenderSceneInfo& info)
{
	return false;
}

void ll::RenderScene::Update(uint32_t stamp)
{
}

void ll::RenderScene::Destroy()
{
}

void ll::RenderScene::Activate()
{
}

void ll::RenderScene::AddCamera(Camera* camera)
{
}

void ll::RenderScene::RemoveCamera(Camera* camera)
{
}

void ll::RenderScene::RemoveCameras()
{
}

void ll::RenderScene::UnsetMainLight(DirectionalLight* dl)
{
}

void ll::RenderScene::AddDirectionalLight(DirectionalLight* dl)
{
}

void ll::RenderScene::RemoveDirectionalLight(DirectionalLight* dl)
{
}

void ll::RenderScene::AddSphereLight(SphereLight*)
{
}

void ll::RenderScene::RemoveSphereLight(SphereLight*)
{
}

void ll::RenderScene::RemoveSphereLights()
{
}

void ll::RenderScene::AddSpotLight(SpotLight*)
{
}

void ll::RenderScene::RemoveSpotLight(SpotLight*)
{
}

void ll::RenderScene::RemoveSpotLights()
{
}

void ll::RenderScene::AddModel(Model*)
{
}

void ll::RenderScene::RemoveModel(Model* model)
{
}

void ll::RenderScene::RemoveModels()
{
}

void ll::RenderScene::AddBatch(DrawBatch2D*)
{
}

void ll::RenderScene::RemoveBatch(DrawBatch2D*)
{
}

void ll::RenderScene::RemoveBatches()
{
}

void ll::RenderScene::OnGlobalPipelineStateChanged()
{
}

void ll::RenderScene::SetMainLight(DirectionalLight* dl)
{
}

void ll::RenderScene::UpdateOctree(Model* model)
{
}
