#pragma once

#include <string>

#include "CBuffer.h"

namespace OGL
{
class Image
{
public:
    int width{ 0 };
    int height{ 0 };
    void* data{ nullptr };
    PixelFormat pixelFormat{ PixelFormat::UNKNOWN };
    ImageDataType imageDataType{ ImageDataType::UNKNOWN };
    ImageDataFormat imageDataFormat{ ImageDataFormat::UNKNOWN };
};
}

