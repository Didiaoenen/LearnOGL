#include "Texture2D.h"

using namespace ll;

ll::Texture2D::Texture2D()
{
}

ll::Texture2D::~Texture2D()
{
}

void ll::Texture2D::SyncMipmapsForJS(const std::vector<IntrusivePtr<ImageAsset>>& value)
{
}

void ll::Texture2D::SetMipmaps(const std::vector<IntrusivePtr<ImageAsset>>& value)
{
}

void ll::Texture2D::SetImage(ImageAsset* value)
{
}

void ll::Texture2D::Initialize()
{
}

void ll::Texture2D::OnLoaded()
{
}

void ll::Texture2D::Reset(const ITexture2DCreateInfo& info)
{
}

void ll::Texture2D::Create(uint32_t width, uint32_t height, PixelFormat format, uint32_t mipmapLevel, uint32_t baseLevel, uint32_t maxLevel)
{
}

std::string ll::Texture2D::ToString() const
{
    return std::string();
}

void ll::Texture2D::UpdateMipmaps(uint32_t firstLevel, uint32_t count)
{
}

bool ll::Texture2D::Destroy()
{
    return false;
}

std::string ll::Texture2D::Description() const
{
    return std::string();
}

void ll::Texture2D::ReleaseTexture()
{
}

TextureInfo ll::Texture2D::GetGfxTextureCreateInfo(TextureUsageBit usage, Format format, uint32_t levelCount, TextureFlagBit flags)
{
    return TextureInfo();
}

TextureViewInfo ll::Texture2D::GetGfxTextureViewCreateInfo(Texture* texture, Format format, uint32_t baseLevel, uint32_t levelCount)
{
    return TextureViewInfo();
}
