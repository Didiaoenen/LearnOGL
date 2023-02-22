#pragma once

#include <map>
#include <string>
#include <variant>

namespace ll
{

using MacroValue = std::variant<int32_t, bool, std::string>;
using MacroRecord = std::map<std::string, MacroValue>;

}