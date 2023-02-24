#include "ImageAsset.h"

using namespace ll;

ll::ImageAsset::~ImageAsset()
{
}

const uint8_t* ll::ImageAsset::GetData() const
{
    return nullptr;
}

uint32_t ll::ImageAsset::GetWidth() const
{
    return 0;
}

uint32_t ll::ImageAsset::GetHeight() const
{
    return 0;
}

PixelFormat ll::ImageAsset::GetFormat() const
{
    return PixelFormat();
}

bool ll::ImageAsset::IsCompressed() const
{
    return false;
}

const std::string& ll::ImageAsset::GetUrl() const
{
    // TODO: 在此处插入 return 语句
}
