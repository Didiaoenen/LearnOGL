#pragma once

#include <string>
#include <variant>

namespace ll
{
using MacroValue = std::variant<int32_t, bool, std::string>;
using MacroRecord = std::unordered_map<std::string, MacroValue>;

}