#pragma once

#include "../base/Def_common.h"

#include "../core/TypedArray.h"

#include <glm/glm.hpp>
#include <vector>
#include <optional>

namespace ll 
{

    struct IGeometryOptions 
    {
        bool includeNormal{ true };
        bool includeUV{ true };
    };

    struct CustomAttribute 
    {
        Attribute attr;
        std::vector<float> values;
    };

    struct IGeometry 
    {
        std::vector<float> positions;
        std::optional<std::vector<float>> normals;
        std::optional<std::vector<float>> uvs;
        std::optional<std::vector<float>> tangents;
        std::optional<std::vector<float>> colors;
        std::optional<AttributeList> attributes;
        std::optional<std::vector<CustomAttribute>> customAttributes;
        std::optional<float> boundingRadius;
        std::optional<glm::vec3> minPos;
        std::optional<glm::vec3> maxPos;
        std::optional<std::vector<uint32_t>> indices; //cjh uint16_t ?
        std::optional<PrimitiveMode> primitiveMode;
        std::optional<bool> doubleSided;
    };

    struct DynamicCustomAttribute 
    {
        Attribute attr;
        Float32Array values;
    };

    struct IDynamicGeometry 
    {
        Float32Array positions;
        std::optional<Float32Array> normals;
        std::optional<Float32Array> uvs;
        std::optional<Float32Array> tangents;
        std::optional<Float32Array> colors;
        std::optional<std::vector<DynamicCustomAttribute>> customAttributes;
        std::optional<glm::vec3> minPos;
        std::optional<glm::vec3> maxPos;
        std::optional<Uint16Array> indices16;
        std::optional<Uint32Array> indices32;
        std::optional<PrimitiveMode> primitiveMode;
        std::optional<bool> doubleSided;
    };

}
