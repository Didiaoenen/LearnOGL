#include "TextureCube.h"

using namespace ll;

ll::TextureCube::~TextureCube()
{
}

TextureCube* ll::TextureCube::FromTexture2DArray(const std::vector<Texture2D*>& textures)
{
    return nullptr;
}

void ll::TextureCube::SetMipmaps(const std::vector<ITextureCubeMipmap>& value)
{
}

void ll::TextureCube::SetMipmapsForJS(const std::vector<ITextureCubeMipmap>& value)
{
}

void ll::TextureCube::SetMipmapAtlasForJS(const TextureCubeMipmapAtlasInfo& value)
{
}

void ll::TextureCube::SetMipmapAtlas(const TextureCubeMipmapAtlasInfo& value)
{
}

void ll::TextureCube::SetImage(const ITextureCubeMipmap* value)
{
}

void ll::TextureCube::Reset(const ITextureCubeCreateInfo& info)
{
}

void ll::TextureCube::ReleaseTexture()
{
}

void ll::TextureCube::UpdateMipmaps(uint32_t firstLevel, uint32_t count)
{
}

bool ll::TextureCube::IsUsingOfflineMipmaps()
{
    return false;
}

void ll::TextureCube::Initialize()
{
}

void ll::TextureCube::OnLoaded()
{
}

bool ll::TextureCube::Destroy()
{
    return false;
}

TextureInfo ll::TextureCube::GetGfxTextureCreateInfo(TextureUsageBit usage, Format format, uint32_t levelCount, TextureFlagBit flags)
{
    return TextureInfo();
}

TextureViewInfo ll::TextureCube::GetGfxTextureViewCreateInfo(Texture* texture, Format format, uint32_t baseLevel, uint32_t levelCount)
{
    return TextureViewInfo();
}
