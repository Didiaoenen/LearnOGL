#pragma once

#include "EffectAsset.h"

namespace ll
{

struct IProgramInfo : public IShaderInfo 
{
    std::string effectName;
    std::vector<IDefineRecord> defines;
    std::string constantMacros;
    bool uber{ false };

    void copyFrom(const IShaderInfo& o);
};

class ProgramLib
{
public:


};

}