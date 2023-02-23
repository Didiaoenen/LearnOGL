#pragma once

#include "../core/PassUtils.h"

#include <string>

namespace ll
{

struct IMacroPatch 
{
    std::string name;
    MacroValue value;
};

}