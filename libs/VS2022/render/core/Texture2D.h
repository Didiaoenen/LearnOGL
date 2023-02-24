#pragma once

#include "SimpleTexture.h"

namespace ll
{

struct ITexture2DCreateInfo 
{
    uint32_t width{ 0 };
    uint32_t height{ 0 };
    std::optional<PixelFormat> format;
    std::optional<uint32_t> mipmapLevel;
    std::optional<uint32_t> baseLevel;
    std::optional<uint32_t> maxLevel;
};

class Texture2D final : public SimpleTexture
{
public:
    using Super = SimpleTexture;

    Texture2D();
    ~Texture2D() override;

    const std::vector<IntrusivePtr<ImageAsset>>& GetMipmaps() const { return _mipmaps; }
    const std::vector<std::string>& GetMipmapsUuids() const { return _mipmapsUuids; }
    void SyncMipmapsForJS(const std::vector<IntrusivePtr<ImageAsset>>& value);
    void SetMipmaps(const std::vector<IntrusivePtr<ImageAsset>>& value);

    inline ImageAsset* GetImage() const { return _mipmaps.empty() ? nullptr : _mipmaps[0].get(); }
    void SetImage(ImageAsset* value);
    void Initialize();
    void OnLoaded() override;

    void Reset(const ITexture2DCreateInfo& info);

    void Create(uint32_t width, uint32_t height, PixelFormat format = PixelFormat::RGBA8888, uint32_t mipmapLevel = 1, uint32_t baseLevel = 0, uint32_t maxLevel = 1000);

    std::string ToString() const override;

    void UpdateMipmaps(uint32_t firstLevel, uint32_t count) override;

    bool Destroy() override;

    std::string Description() const;

    void ReleaseTexture();

    TextureInfo GetGfxTextureCreateInfo(TextureUsageBit usage, Format format, uint32_t levelCount, TextureFlagBit flags) override;
    TextureViewInfo GetGfxTextureViewCreateInfo(Texture* texture, Format format, uint32_t baseLevel, uint32_t levelCount) override;

private:
    std::vector<IntrusivePtr<ImageAsset>> _mipmaps;

    std::vector<std::string> _mipmapsUuids;

    friend class Texture2DDeserializer;

    DISALLOW_COPY_MOVE_ASSIGN(Texture2D)
};

}