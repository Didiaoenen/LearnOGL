#pragma once

#include <vector>
#include <memory>
#include <unordered_map>

#include "OGL_Component.h"
#include "OGL_Base.h"
#include "OGL_Mesh.h"
#include "OGL_Material.h"

namespace OGL
{
class OGL_MeshRenderer : public OGL_Component
{
public:
	OGL_MeshRenderer() = default;
	virtual ~OGL_MeshRenderer() = default;

public:
	std::vector<Ref<OGL_Mesh>> mMeshs;
	std::unordered_map<std::string, Ref<OGL_Material>> mMaterials;
};
}

