#pragma once

#include "BaseSceneNode.h"

namespace OGL
{
class SceneLightNode : public SceneNode<SceneObjectLight>
{
public:
	using SceneNode::SceneNode;

	void SetCastShadow(bool castShadow) { mCastShadow = castShadow; }

protected:
	bool mCastShadow;
};
}
