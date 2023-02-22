#pragma once

#include "../base/Ptr.h"
#include "../base/Macros.h"

#include <vector>
#include <string>

namespace ll
{

class Model;
class Octree;
class Camera;
class DrawBatch2D;
class SpotLight;
class SphereLight;
class DirectionalLight;


struct IRenderSceneInfo 
{
    std::string name;
};


class RenderScene
{
public:
    RenderScene();
    virtual ~RenderScene();

    bool Initialize(const IRenderSceneInfo& info);
    void Update(uint32_t stamp);
    void Destroy();

    void Activate();

    void AddCamera(Camera* camera);
    void RemoveCamera(Camera* camera);
    void RemoveCameras();

    void UnsetMainLight(DirectionalLight* dl);
    void AddDirectionalLight(DirectionalLight* dl);
    void RemoveDirectionalLight(DirectionalLight* dl);

    void AddSphereLight(SphereLight*);
    void RemoveSphereLight(SphereLight*);
    void RemoveSphereLights();

    void AddSpotLight(SpotLight*);
    void RemoveSpotLight(SpotLight*);
    void RemoveSpotLights();

    void AddModel(Model*);
    void RemoveModel(Model* model);
    void RemoveModels();

    void AddBatch(DrawBatch2D*);
    void RemoveBatch(DrawBatch2D*);
    void RemoveBatches();

    void OnGlobalPipelineStateChanged();

    inline DirectionalLight* GetMainLight() const { return _mainLight.get(); }
    void SetMainLight(DirectionalLight* dl);

    inline uint64_t GenerateModelId() { return _modelId++; }
    inline const std::string& GetName() const { return _name; }
    inline const std::vector<IntrusivePtr<Camera>>& GetCameras() const { return _cameras; }
    inline const std::vector<IntrusivePtr<SphereLight>>& GetSphereLights() const { return _sphereLights; }
    inline const std::vector<IntrusivePtr<SpotLight>>& GetSpotLights() const { return _spotLights; }
    inline const std::vector<IntrusivePtr<Model>>& GetModels() const { return _models; }
    inline Octree* GetOctree() const { return _octree; }
    void UpdateOctree(Model* model);
    inline const std::vector<DrawBatch2D*>& GetBatches() const { return _batches; }

private:
    std::string _name;
    uint64_t _modelId{ 0 };
    IntrusivePtr<DirectionalLight> _mainLight;
    std::vector<IntrusivePtr<Model>> _models;
    std::vector<IntrusivePtr<Camera>> _cameras;
    std::vector<IntrusivePtr<DirectionalLight>> _directionalLights;
    std::vector<IntrusivePtr<SphereLight>> _sphereLights;
    std::vector<IntrusivePtr<SpotLight>> _spotLights;
    std::vector<DrawBatch2D*> _batches;
    Octree* _octree{ nullptr };

    DISALLOW_COPY_MOVE_ASSIGN(RenderScene)
};

}