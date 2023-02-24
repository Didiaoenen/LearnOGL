#pragma once

#include "Types.h"

#include <string>

namespace ll
{

struct IMeshBufferView 
{
    uint32_t offset{ 0 };
    uint32_t length{ 0 };
    uint32_t count{ 0 };
    uint32_t stride{ 0 };
};

struct MorphTarget 
{
    std::vector<IMeshBufferView> displacements;
};

struct SubMeshMorph 
{
    std::vector<std::string> attributes;
    std::vector<MorphTarget> targets;
    std::optional<MeshWeightsType> weights;
};

struct Morph 
{
    std::vector<std::optional<SubMeshMorph>> subMeshMorphs;
    std::optional<MeshWeightsType> weights;
    std::optional<std::vector<std::string>> targetNames;
};


}