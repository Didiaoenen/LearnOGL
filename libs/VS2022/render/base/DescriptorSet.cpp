#include "DescriptorSet.h"

ll::DescriptorSet::DescriptorSet()
	:ll::Object(ObjectType::DESCRIPTOR_SET)
{
}

ll::DescriptorSet::~DescriptorSet()
{
}

void ll::DescriptorSet::Initialize(const DescriptorSetInfo& info)
{
}

void ll::DescriptorSet::Destroy()
{
}

void ll::DescriptorSet::BindBuffer(uint32_t binding, Buffer* buffer, uint32_t index)
{
}

void ll::DescriptorSet::BindTexture(uint32_t binding, Texture* texture, uint32_t index)
{
}

void ll::DescriptorSet::BindSampler(uint32_t binding, Sampler* sampler, uint32_t index)
{
}

ll::Buffer* ll::DescriptorSet::GetBuffer(uint32_t binding, uint32_t index) const
{
	return nullptr;
}

ll::Texture* ll::DescriptorSet::GetTexture(uint32_t binding, uint32_t index) const
{
	return nullptr;
}

ll::Sampler* ll::DescriptorSet::GetSampler(uint32_t binding, uint32_t index) const
{
	return nullptr;
}
