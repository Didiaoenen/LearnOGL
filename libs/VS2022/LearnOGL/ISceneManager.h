#pragma once

#include <string>
#include <memory>

#include "IRuntimeModule.h"

#include "Scene.h"
#include "BaseSceneNode.h"

namespace OGL
{
class ISceneManager : public IRuntimeModule
{
public:
    ISceneManager() = default;
    virtual ~ISceneManager() = default;

    virtual bool LoadScene(const std::string& sceneName) = 0;

    virtual uint64_t GetSceneRevision() const = 0;

    virtual const std::shared_ptr<Scene> GetSceneForRendering() const = 0;

    virtual std::weak_ptr<BaseSceneNode> GetRootNode() const = 0;
    virtual std::weak_ptr<SceneGeometryNode> GetSceneGeometryNode(const std::string& name) const = 0;
    virtual std::weak_ptr<SceneObjectGeometry> GetSceneGeometryObject(const std::string& key) const = 0;
};
}