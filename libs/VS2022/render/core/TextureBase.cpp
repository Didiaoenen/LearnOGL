#include "TextureBase.h"

using namespace ll;

ll::TextureBase::TextureBase()
{
}

ll::TextureBase::~TextureBase()
{
}

bool ll::TextureBase::IsCompressed() const
{
    return false;
}

void ll::TextureBase::SetWrapMode(WrapMode wrapS, WrapMode wrapT, WrapMode wrapR)
{
}

void ll::TextureBase::SetWrapMode(WrapMode wrapS, WrapMode wrapT)
{
}

void ll::TextureBase::SetFilters(Filter minFilter, Filter magFilter)
{
}

void ll::TextureBase::SetMipFilter(Filter mipFilter)
{
}

void ll::TextureBase::SetAnisotropy(uint32_t anisotropy)
{
}

bool ll::TextureBase::Destroy()
{
    return false;
}

Sampler* ll::TextureBase::GetGFXSampler() const
{
    return nullptr;
}

Device* ll::TextureBase::GetGFXDevice()
{
    return nullptr;
}

Format ll::TextureBase::GetGFXPixelFormat(PixelFormat format)
{
    return Format();
}

Format ll::TextureBase::GetGFXFormat() const
{
    return Format();
}

void ll::TextureBase::SetGFXFormat(const std::optional<PixelFormat>& format)
{
}

void ll::TextureBase::NotifySamplerUpdated()
{
}
