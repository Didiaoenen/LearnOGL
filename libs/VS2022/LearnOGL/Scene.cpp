#include "Scene.h"

using namespace OGL;

shared_ptr<SceneObjectCamera> Scene::GetCamera(const string& key) const
{
    auto i = mCameras.find(key);
    if (i == mCameras.end()) 
    {
        return nullptr;
    }

    return i->second;
}

shared_ptr<SceneObjectGeometry> Scene::GetGeometry(const string& key) const
{
    auto i = mGeometries.find(key);
    if (i == mGeometries.end())
    {
        return nullptr;
    }

    return i->second;
}

shared_ptr<SceneObjectMaterial> Scene::GetMaterial(const string& key) const
{
    auto i = mMaterials.find(key);
    if (i == mMaterials.end())
    {
        return mDefaultMaterial;
    }

    return i->second;
}

shared_ptr<SceneObjectLight> Scene::GetLight(const string& key) const
{
    auto i = mLights.find(key);
    if (i == mLights.end())
    {
        return nullptr;
    }

    return i->second;
}

shared_ptr<SceneCameraNode> Scene::GetFirstCameraNode() const
{
    return mCameraNodes.empty() ? nullptr : mCameraNodes.cbegin()->second;
}

shared_ptr<BaseSceneNode> Scene::GetSceneNode(const string& key)
{
    
    auto light = mLightNodes.find(key);
    if (light != mLightNodes.end())
    {
        return light->second;
    }

    auto camera = mCameraNodes.find(key);
    if (camera != mCameraNodes.end())
    {
        return camera->second;
    }

    return nullptr;
}

shared_ptr<OGL_Entity> Scene::CreateEntity(const std::string& name)
{
    auto entity = std::make_shared<OGL_Entity>();
    entity->AddComponent<OGL_TagComponent>(name);
    mEntitys.emplace(std::make_pair(name, entity));
    return entity;
}

shared_ptr<OGL_Entity> Scene::GetEntity(const std::string& name)
{
    auto entity = mEntitys.find(name);
    if (entity != mEntitys.end())
    {
        return entity->second;
    }
    return nullptr;
}
