#pragma once

#include <vector>
#include <string>

#include "OGL_Asset.h"
#include "CBuffer.h"

namespace OGL
{
class OGL_Mesh : public OGL_Asset
{
public:
    OGL_Mesh() = default;
    OGL_Mesh(const std::string& name): mName(name) {}
    virtual ~OGL_Mesh() = default;

public:
    std::string mName;
    std::vector<_Vertex> mVertices;
    std::vector<uint32_t> mIndices;

    bool hasNormal{ false };
    bool hasVertexColors{ false };
    bool hasTextureCoords{ false };
    bool hasTangentsAndBitangents{ false };

    uint32_t mPrimitiveTypes{ 0 };
};
}