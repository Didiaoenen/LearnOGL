#include "SimpleTexture.h"

using namespace ll;

ll::SimpleTexture::~SimpleTexture()
{
}

bool ll::SimpleTexture::Destroy()
{
    return false;
}

void ll::SimpleTexture::UpdateImage()
{
}

void ll::SimpleTexture::UploadDataWithArrayBuffer(const ArrayBuffer& source, uint32_t level, uint32_t arrayIndex)
{
}

void ll::SimpleTexture::UploadData(const uint8_t* source, uint32_t level, uint32_t arrayIndex)
{
}

void ll::SimpleTexture::AssignImage(ImageAsset* image, uint32_t level, uint32_t arrayIndex)
{
}

void ll::SimpleTexture::CheckTextureLoaded()
{
}

void ll::SimpleTexture::SetMipmapLevel(uint32_t value)
{
}

void ll::SimpleTexture::SetMipRange(uint32_t baseLevel, uint32_t maxLevel)
{
}

bool ll::SimpleTexture::IsUsingOfflineMipmaps()
{
    return false;
}

ll::SimpleTexture::SimpleTexture()
{
}

void ll::SimpleTexture::TextureReady()
{
}

void ll::SimpleTexture::TryReset()
{
}

void ll::SimpleTexture::CreateTexture(Device* device)
{
}

Texture* ll::SimpleTexture::CreateTextureView(Device* device)
{
    return nullptr;
}

void ll::SimpleTexture::TryDestroyTexture()
{
}

void ll::SimpleTexture::TryDestroyTextureView()
{
}

void ll::SimpleTexture::NotifyTextureUpdated()
{
}

void ll::SimpleTexture::SetMipRangeInternal(uint32_t baseLevel, uint32_t maxLevel)
{
}
