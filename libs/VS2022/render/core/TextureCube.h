#pragma once

#include "SimpleTexture.h"

namespace ll
{

class Texture2D;
class ImageAsset;
struct ITexture2DCreateInfo;

using ITextureCubeCreateInfo = ITexture2DCreateInfo;

struct ITextureCubeMipmap 
{
    IntrusivePtr<ImageAsset> front;
    IntrusivePtr<ImageAsset> back;
    IntrusivePtr<ImageAsset> left;
    IntrusivePtr<ImageAsset> right;
    IntrusivePtr<ImageAsset> top;
    IntrusivePtr<ImageAsset> bottom;
};

struct MipmapAtlasLayoutInfo 
{
    uint32_t left{ 0 };
    uint32_t top{ 0 };
    uint32_t width{ 0 };
    uint32_t height{ 0 };
    uint32_t level{ 0 };
};

struct TextureCubeMipmapAtlasInfo 
{
    ITextureCubeMipmap atlas;
    std::vector<MipmapAtlasLayoutInfo> layout;
};

enum class MipmapMode 
{
    NONE = 0,
    AUTO = 1,
    BAKED_CONVOLUTION_MAP = 2
};

class TextureCube final : public SimpleTexture
{
    using Super = SimpleTexture;

    TextureCube();
    ~TextureCube() override;

    enum class FaceIndex 
    {
        RIGHT = 0,
        LEFT = 1,
        TOP = 2,
        BOTTOM = 3,
        FRONT = 4,
        BACK = 5,
    };

    static TextureCube* FromTexture2DArray(const std::vector<Texture2D*>& textures);
    const std::vector<ITextureCubeMipmap>& GetMipmaps() const { return _mipmaps; }
    inline const TextureCubeMipmapAtlasInfo& GetMipmapAtlas() const { return _mipmapAtlas; }
    void SetMipmaps(const std::vector<ITextureCubeMipmap>& value);
    void SetMipmapsForJS(const std::vector<ITextureCubeMipmap>& value);
    void SetMipmapAtlasForJS(const TextureCubeMipmapAtlasInfo& value);
    void SetMipmapAtlas(const TextureCubeMipmapAtlasInfo& value);
    const ITextureCubeMipmap* getImage() const { return _mipmaps.empty() ? nullptr : &_mipmaps[0]; }
    void SetImage(const ITextureCubeMipmap* value);
    void Reset(const ITextureCubeCreateInfo& info);
    void ReleaseTexture();
    void UpdateMipmaps(uint32_t firstLevel, uint32_t count) override;
    bool IsUsingOfflineMipmaps() override;
    void Initialize();
    void OnLoaded() override;
    bool Destroy() override;

    TextureInfo GetGfxTextureCreateInfo(TextureUsageBit usage, Format format, uint32_t levelCount, TextureFlagBit flags) override;
    TextureViewInfo GetGfxTextureViewCreateInfo(Texture* texture, Format format, uint32_t baseLevel, uint32_t levelCount) override;

    MipmapMode _mipmapMode{ MipmapMode::NONE };
    bool isRGBE{ false };

private:
    std::vector<ITextureCubeMipmap> _mipmaps;
    TextureCubeMipmapAtlasInfo _mipmapAtlas;
    
    DISALLOW_COPY_MOVE_ASSIGN(TextureCube)
};

}