#pragma once

#include <stack>
#include <string>
#include <memory>

#include "ISceneManager.h"

using namespace std;

namespace OGL
{
class SceneManager : public ISceneManager
{
public:
	SceneManager() = default;
	~SceneManager() = default;

	bool Initialize() override;
	void Finalize() override;

	void Tick() override;

	bool LoadScene(const string& sceneName) override;

	uint64_t GetSceneRevision() const override { return mSceneRevision; }

	const shared_ptr<Scene> GetSceneForRendering() const override;

	void ResetScene() override { mSceneRevision++; };

	shared_ptr<BaseSceneNode> GetRootNode() const override;
	shared_ptr<SceneGeometryNode> GetSceneGeometryNode(const string& name) const override;
	shared_ptr<SceneObjectGeometry> GetSceneGeometryObject(const string& key) const override;

protected:
	stack<shared_ptr<Scene>> mScenes;
	uint64_t mSceneRevision{ 0 };
};
}