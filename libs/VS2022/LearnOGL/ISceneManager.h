#pragma once

#include <string>
#include <memory>

#include "IRuntimeModule.h"

#include "Scene.h"
#include "BaseSceneNode.h"

using namespace std;

namespace OGL
{
class ISceneManager : public IRuntimeModule
{
public:
    ISceneManager() = default;
    virtual ~ISceneManager() = default;

    virtual bool LoadScene(const string& sceneName) = 0;

    virtual uint64_t GetSceneRevision() const = 0;

    virtual const shared_ptr<Scene> GetSceneForRendering() const = 0;

    virtual void ResetScene() = 0;

    virtual weak_ptr<BaseSceneNode> GetRootNode() const = 0;
    virtual weak_ptr<SceneGeometryNode> GetSceneGeometryNode(const string& name) const = 0;
    virtual weak_ptr<SceneObjectGeometry> GetSceneGeometryObject(const string& key) const = 0;
};
}