#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "SceneObjectTexture.h"

using namespace std;
using namespace glm;

namespace OGL
{
template <typename T>
struct ParameterValueMap 
{
    T Value = (T)0;
    shared_ptr<SceneObjectTexture> ValueMap;

    ParameterValueMap() = default;
    ~ParameterValueMap() = default;

    explicit ParameterValueMap(const T value)
        : Value(value), ValueMap(nullptr) 
    {
    }

    explicit ParameterValueMap(shared_ptr<SceneObjectTexture> value)
        : ValueMap(std::move(value)) 
    {
    }

    ParameterValueMap& operator=(const shared_ptr<SceneObjectTexture>& rhs) 
    {
        ValueMap = rhs;
        return *this;
    }

    ParameterValueMap& operator=(shared_ptr<SceneObjectTexture>&& rhs) 
    {
        ValueMap.swap(rhs);
        return *this;
    }

};

using Color = ParameterValueMap<vec4>;
using Normal = ParameterValueMap<vec3>;
using Parameter = ParameterValueMap<float>;
}