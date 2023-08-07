#pragma once

#include <memory>
#include <unordered_map>

#include "SceneNode.h"
#include "SceneObject.h"

using namespace std;

namespace OGL
{
class Scene
{
public:
	[[nodiscard]] shared_ptr<SceneObjectLight> GetLight(const string& key) const;

	[[nodiscard]] shared_ptr<SceneObjectCamera> GetCamera(const string& key) const;

	[[nodiscard]] shared_ptr<SceneObjectGeometry> GetGeometry(const string& key) const;

	[[nodiscard]] shared_ptr<SceneCameraNode> GetFirstCameraNode() const;
	
public:
	shared_ptr<BaseSceneNode> mSceneGraph;

	unordered_map<string, shared_ptr<SceneObjectLight>> mLights;
	
	unordered_map<string, shared_ptr<SceneObjectCamera>> mCameras;

	unordered_map<string, shared_ptr<SceneObjectGeometry>> mGeometries;

	unordered_map<string, shared_ptr<SceneObjectMaterial>> mMaterials;

	unordered_multimap<string, weak_ptr<SceneLightNode>> mLightNodes;

	unordered_multimap<string, weak_ptr<SceneCameraNode>> mCameraNodes;

	unordered_multimap<string, weak_ptr<SceneGeometryNode>> mGeometryNodes;

	shared_ptr<SceneObjectSkyBox> mSkyBox;
};
}
