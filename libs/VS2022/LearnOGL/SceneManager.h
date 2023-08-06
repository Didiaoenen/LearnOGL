#pragma once

#include <stack>

#include "ISceneManager.h"

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

	bool LoadScene(const std::string& sceneName) override;

	uint64_t GetSceneRevision() const override { return mSceneRevision; }

	const std::shared_ptr<Scene> GetSceneForRendering() const override;

	std::weak_ptr<BaseSceneNode> GetRootNode() const override;
	std::weak_ptr<SceneGeometryNode> GetSceneGeometryNode(const std::string& name) const override;
	std::weak_ptr<SceneObjectGeometry> GetSceneGeometryObject(const std::string& key) const override;

protected:
	stack<shared_ptr<Scene>> mScenes;
	uint64_t mSceneRevision{ 0 };
};
}