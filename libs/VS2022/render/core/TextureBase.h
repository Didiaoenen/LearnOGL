#pragma once

#include "../base/Macros.h"
#include "../base/Def_common.h"

#include "Asset.h"
#include "AssetEnum.h"

#include <optional>

namespace ll
{

class Device;
class Sampler;
class Texture;

class TextureBase : public Asset
{
public:
    using Super = Asset;

    using PixelFormat = PixelFormat;
    using WrapMode = WrapMode;
    using Filter = Filter;

    TextureBase();
    ~TextureBase() override;
    bool IsCompressed() const;

    uint32_t GetWidth() const { return _width; }
    uint32_t GetHeight() const { return _height; }

    inline void SetWidth(uint32_t width) { _width = width; }
    inline void SetHeight(uint32_t height) { _height = height; }

    inline const std::string& GetId() const { return _id; }
    inline PixelFormat GetPixelFormat() const { return _format; }
    inline uint32_t GetAnisotropy() const { return _anisotropy; }

    void SetWrapMode(WrapMode wrapS, WrapMode wrapT, WrapMode wrapR);
    void SetWrapMode(WrapMode wrapS, WrapMode wrapT);

    void SetFilters(Filter minFilter, Filter magFilter);
    void SetMipFilter(Filter mipFilter);

    void SetAnisotropy(uint32_t anisotropy);

    bool Destroy() override;

    virtual Texture* GetGFXTexture() const { return nullptr; }

    virtual const SamplerInfo& GetSamplerInfo() const { return _samplerInfo; }

    virtual Sampler* GetGFXSampler() const;

protected:
    static Device* GetGFXDevice();
    static Format GetGFXPixelFormat(PixelFormat format);

    Format GetGFXFormat() const;

    void SetGFXFormat(const std::optional<PixelFormat>& format);

private:
    void NotifySamplerUpdated();

public:
    PixelFormat _format{ PixelFormat::RGBA8888 };
    Filter _minFilter{ Filter::LINEAR };
    Filter _magFilter{ Filter::LINEAR };
    Filter _mipFilter{ Filter::NONE };
    WrapMode _wrapS{ WrapMode::REPEAT };
    WrapMode _wrapT{ WrapMode::REPEAT };
    WrapMode _wrapR{ WrapMode::REPEAT };
    uint32_t _anisotropy{ 0 };
    uint32_t _width{ 1 };
    uint32_t _height{ 1 };

protected:
    std::string _id;
    SamplerInfo _samplerInfo;
    Sampler* _gfxSampler{ nullptr };
    Device* _gfxDevice{ nullptr };

private:
    DISALLOW_COPY_MOVE_ASSIGN(TextureBase)
};

}

