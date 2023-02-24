#pragma once

#include "../core/ArrayBuffer.h"

#include "Asset.h"
#include "AssetEnum.h"

namespace ll
{

class ImageAsset final : public Asset
{
    using Super = Asset;

    ImageAsset() = default;
    ~ImageAsset() override;

    const uint8_t* GetData() const;
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    PixelFormat GetFormat() const;
    bool IsCompressed() const;
    const std::string& GetUrl() const;

    inline void SetWidth(uint32_t width) { _width = width; }
    inline void SetHeight(uint32_t height) { _height = height; }
    inline void SetFormat(PixelFormat format) { _format = format; }
    inline void SetData(uint8_t* data) { _data = data; }
    inline void SetUrl(const std::string& url) { _url = url; }

private:
    uint32_t _width{ 0 };
    uint32_t _height{ 0 };
    PixelFormat _format{ PixelFormat::RGBA8888 };
    uint8_t* _data{ nullptr };
    bool _needFreeData{ false };
    ArrayBuffer::Ptr _arrayBuffer;
    std::string _url;

    DISALLOW_COPY_MOVE_ASSIGN(ImageAsset)
};

}