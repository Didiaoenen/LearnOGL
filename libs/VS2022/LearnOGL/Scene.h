#pragma once

#include <memory>
#include <unordered_map>

#include "SceneNode.h"
#include "SceneObjectBase.h"

#include "OGL_UUID.h"
#include "OGL_Entity.h"

namespace OGL
{
class Scene
{
public:
	[[nodiscard]] shared_ptr<SceneObjectLight> GetLight(const string& key) const;

	[[nodiscard]] shared_ptr<SceneObjectCamera> GetCamera(const string& key) const;

	[[nodiscard]] shared_ptr<SceneObjectGeometry> GetGeometry(const string& key) const;

	[[nodiscard]] shared_ptr<SceneObjectMaterial> GetMaterial(const string& key) const;

	[[nodiscard]] shared_ptr<SceneCameraNode> GetFirstCameraNode() const;

	[[nodiscard]] shared_ptr<BaseSceneNode> GetSceneNode(const string& key);
	
	[[nodiscard]] shared_ptr<OGL_Entity> CreateEntity(const std::string& name = std::string());

	[[nodiscard]] shared_ptr<OGL_Entity> GetEntity(const std::string& name);

public:
	shared_ptr<BaseSceneNode> mSceneGraph;

	unordered_map<string, shared_ptr<SceneObjectLight>> mLights;
	
	unordered_map<string, shared_ptr<SceneObjectCamera>> mCameras;

	unordered_map<string, shared_ptr<SceneObjectGeometry>> mGeometries;

	unordered_map<string, shared_ptr<SceneObjectMaterial>> mMaterials;

	unordered_multimap<string, shared_ptr<SceneLightNode>> mLightNodes;

	unordered_multimap<string, shared_ptr<SceneCameraNode>> mCameraNodes;

	unordered_multimap<string, shared_ptr<SceneGeometryNode>> mGeometryNodes;

	std::unordered_map<std::string, shared_ptr<OGL_Entity>> mEntitys;

	shared_ptr<SceneObjectSkyBox> mSkyBox;

private:
	shared_ptr<SceneObjectMaterial> mDefaultMaterial = make_shared<SceneObjectMaterial>("default");
};
}
