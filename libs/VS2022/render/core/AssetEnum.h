#pragma once

#include <string>

namespace ll
{

enum class PixelFormat : uint32_t 
{
    RGB565 = static_cast<uint32_t>(Format::R5G6B5),
    RGB5A1 = static_cast<uint32_t>(Format::RGB5A1),
    RGBA4444 = static_cast<uint32_t>(Format::RGBA4),
    RGB888 = static_cast<uint32_t>(Format::RGB8),
    RGB32F = static_cast<uint32_t>(Format::RGB32F),
    RGBA8888 = static_cast<uint32_t>(Format::RGBA8),
    RGBA32F = static_cast<uint32_t>(Format::RGBA32F),
    A8 = static_cast<uint32_t>(Format::A8),
    I8 = static_cast<uint32_t>(Format::L8),
    AI8 = static_cast<uint32_t>(Format::LA8),
    RGB_PVRTC_2BPPV1 = static_cast<uint32_t>(Format::PVRTC_RGB2),
    RGBA_PVRTC_2BPPV1 = static_cast<uint32_t>(Format::PVRTC_RGBA2),
    RGB_A_PVRTC_2BPPV1 = CUSTOM_PIXEL_FORMAT,
    RGB_PVRTC_4BPPV1 = static_cast<uint32_t>(Format::PVRTC_RGB4),
    RGBA_PVRTC_4BPPV1 = static_cast<uint32_t>(Format::PVRTC_RGBA4),
    RGB_A_PVRTC_4BPPV1 = CUSTOM_PIXEL_FORMAT + 1,
    RGB_ETC1 = static_cast<uint32_t>(Format::ETC_RGB8),
    RGBA_ETC1 = CUSTOM_PIXEL_FORMAT + 2,
    RGB_ETC2 = static_cast<uint32_t>(Format::ETC2_RGB8),
    RGBA_ETC2 = static_cast<uint32_t>(Format::ETC2_RGBA8),
    RGBA_ASTC_4X4 = static_cast<uint32_t>(Format::ASTC_RGBA_4X4),
    RGBA_ASTC_5X4 = static_cast<uint32_t>(Format::ASTC_RGBA_5X4),
    RGBA_ASTC_5X5 = static_cast<uint32_t>(Format::ASTC_RGBA_5X5),
    RGBA_ASTC_6X5 = static_cast<uint32_t>(Format::ASTC_RGBA_6X5),
    RGBA_ASTC_6X6 = static_cast<uint32_t>(Format::ASTC_RGBA_6X6),
    RGBA_ASTC_8X5 = static_cast<uint32_t>(Format::ASTC_RGBA_8X5),
    RGBA_ASTC_8X6 = static_cast<uint32_t>(Format::ASTC_RGBA_8X6),
    RGBA_ASTC_8X8 = static_cast<uint32_t>(Format::ASTC_RGBA_8X8),
    RGBA_ASTC_10X5 = static_cast<uint32_t>(Format::ASTC_RGBA_10X5),
    RGBA_ASTC_10X6 = static_cast<uint32_t>(Format::ASTC_RGBA_10X6),
    RGBA_ASTC_10X8 = static_cast<uint32_t>(Format::ASTC_RGBA_10X8),
    RGBA_ASTC_10X10 = static_cast<uint32_t>(Format::ASTC_RGBA_10X10),
    RGBA_ASTC_12X10 = static_cast<uint32_t>(Format::ASTC_RGBA_12X10),
    RGBA_ASTC_12X12 = static_cast<uint32_t>(Format::ASTC_RGBA_12X12),
};

enum class WrapMode : uint32_t 
{
    REPEAT = static_cast<uint32_t>(Address::WRAP),
    CLAMP_TO_EDGE = static_cast<uint32_t>(Address::CLAMP),
    MIRRORED_REPEAT = static_cast<uint32_t>(Address::MIRROR),
    CLAMP_TO_BORDER = static_cast<uint32_t>(Address::BORDER),
};

enum class Filter : uint32_t 
{
    NONE = static_cast<uint32_t>(Filter::NONE),
    LINEAR = static_cast<uint32_t>(Filter::LINEAR),
    NEAREST = static_cast<uint32_t>(Filter::POINT),
};


}