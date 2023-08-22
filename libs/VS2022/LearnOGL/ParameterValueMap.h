#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "OGL_Base.h"
#include "OGL_Texture.h"

namespace OGL
{
template <typename T>
struct ParameterValueMap 
{
    T Value = (T)0;
    Ref<OGL_Texture> ValueMap;

    ParameterValueMap() = default;
    ~ParameterValueMap() = default;

    explicit ParameterValueMap(const T value)
        : Value(value), ValueMap(nullptr) 
    {
    }

    explicit ParameterValueMap(Ref<OGL_Texture> value)
        : ValueMap(std::move(value)) 
    {
    }

    ParameterValueMap& operator=(const Ref<OGL_Texture>& rhs)
    {
        ValueMap = rhs;
        return *this;
    }

    ParameterValueMap& operator=(Ref<OGL_Texture>&& rhs)
    {
        ValueMap.swap(rhs);
        return *this;
    }

};

using Color = ParameterValueMap<glm::vec4>;
using Normal = ParameterValueMap<glm::vec3>;
using Parameter = ParameterValueMap<float>;
}