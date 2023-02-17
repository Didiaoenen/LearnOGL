#pragma once

#include "Def_common.h"

namespace ll
{
struct SwapchainTextureInfo final 
{
    Swapchain* swapchain{ nullptr };
    Format format{ Format::UNKNOWN };
    uint32_t width{ 0 };
    uint32_t height{ 0 };
};

extern const FormatInfo GFX_FORMAT_INFOS[];

class Executable 
{
public:
    virtual ~Executable() = default;
    virtual void execute() = 0;
};

}