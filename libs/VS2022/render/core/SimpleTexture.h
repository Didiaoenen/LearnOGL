#pragma once

#include "../base/Ptr.h"
#include "../base/Macros.h"
#include "../core/ArrayBuffer.h"

#include "TextureBase.h"

namespace ll
{

class ImageAsset;

class SimpleTexture : public TextureBase
{
public:
    using Super = TextureBase;

    ~SimpleTexture() override;

    inline uint32_t MipmapLevel() const { return _mipmapLevel; }

    Texture* GetGFXTexture() const override { return _gfxTextureView.get(); }

    bool Destroy() override;

    void UpdateImage();

    virtual void UpdateMipmaps(uint32_t firstLevel, uint32_t count) {}

    void UploadDataWithArrayBuffer(const ArrayBuffer& source, uint32_t level = 0, uint32_t arrayIndex = 0);
    void UploadData(const uint8_t* source, uint32_t level = 0, uint32_t arrayIndex = 0);

    void AssignImage(ImageAsset* image, uint32_t level, uint32_t arrayIndex = 0);

    void CheckTextureLoaded();

    void SetMipmapLevel(uint32_t value);

    void SetMipRange(uint32_t baseLevel, uint32_t maxLevel);

    virtual bool IsUsingOfflineMipmaps();

protected:
    SimpleTexture();
    void TextureReady();

    virtual TextureInfo GetGfxTextureCreateInfo(TextureUsageBit usage, Format format, uint32_t levelCount, TextureFlagBit flags) = 0;
    virtual TextureViewInfo GetGfxTextureViewCreateInfo(Texture* texture, Format format, uint32_t baseLevel, uint32_t levelCount) = 0;

    void TryReset();

    void CreateTexture(Device* device);
    Texture* CreateTextureView(Device* device);

    void TryDestroyTexture();
    void TryDestroyTextureView();
    void NotifyTextureUpdated();
    void SetMipRangeInternal(uint32_t baseLevel, uint32_t maxLevel);

    IntrusivePtr<Texture> _gfxTexture;
    IntrusivePtr<Texture> _gfxTextureView;

    uint32_t _mipmapLevel{ 1 };
    uint32_t _textureWidth{ 0 };
    uint32_t _textureHeight{ 0 };

    uint32_t _baseLevel{ 0 };
    uint32_t _maxLevel{ 1000 };

    DISALLOW_COPY_MOVE_ASSIGN(SimpleTexture)
};

}