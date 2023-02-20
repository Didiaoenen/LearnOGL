#pragma once

#include "Def_common.h"

namespace ll
{

class Sampler
{
public:
    explicit Sampler(const SamplerInfo& info);
    inline const SamplerInfo& GetInfo() const { return _info; }

protected:
    SamplerInfo _info;
};

}