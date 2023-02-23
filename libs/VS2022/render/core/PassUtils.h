#pragma once

#include "../base/Ptr.h"

#include <glm/glm.hpp>
#include <map>
#include <string>
#include <variant>

namespace ll
{

class Texture;
class TextureBase;

using MacroValue = std::variant<int32_t, bool, std::string>;
using MacroRecord = std::map<std::string, MacroValue>;

using MaterialProperty = std::variant<std::monostate /*0*/, float /*1*/, int32_t /*2*/, glm::vec2 /*3*/, glm::vec3 /*4*/, glm::vec4 /*5*/, Color, /*6*/ glm::mat3 /*7*/, glm::mat4 /*8*/, glm::quat /*9*/, IntrusivePtr<TextureBase> /*10*/, IntrusivePtr<Texture> /*11*/ >;

using MaterialPropertyList = std::vector<MaterialProperty>;

using MaterialPropertyVariant = std::variant<std::monostate /*0*/, MaterialProperty /*1*/, MaterialPropertyList /*2*/ >;

}