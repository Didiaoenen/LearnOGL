#pragma once

#include "Object.h"

namespace ll
{

class DescriptorSet : public Object
{
public:
    DescriptorSet();
    virtual ~DescriptorSet();

    void Initialize(const DescriptorSetInfo& info);
    void Destroy();

    virtual void Update() = 0;
    virtual void ForceUpdate() = 0;

    virtual void BindBuffer(uint32_t binding, Buffer* buffer, uint32_t index);
    virtual void BindTexture(uint32_t binding, Texture* texture, uint32_t index);
    virtual void BindSampler(uint32_t binding, Sampler* sampler, uint32_t index);

    Buffer* GetBuffer(uint32_t binding, uint32_t index) const;
    Texture* GetTexture(uint32_t binding, uint32_t index) const;
    Sampler* GetSampler(uint32_t binding, uint32_t index) const;

    inline DescriptorSetLayout* GetLayout() const { return _layout; }

    inline void BindBuffer(uint32_t binding, Buffer* buffer) { BindBuffer(binding, buffer, 0U); }
    inline void BindTexture(uint32_t binding, Texture* texture) { BindTexture(binding, texture, 0U); }
    inline void BindSampler(uint32_t binding, Sampler* sampler) { BindSampler(binding, sampler, 0U); }
    inline Buffer* GetBuffer(uint32_t binding) const { return GetBuffer(binding, 0U); }
    inline Texture* GetTexture(uint32_t binding) const { return GetTexture(binding, 0U); }
    inline Sampler* GetSampler(uint32_t binding) const { return GetSampler(binding, 0U); }

protected:
    virtual void DoInit(const DescriptorSetInfo& info) = 0;
    virtual void DoDestroy() = 0;

    DescriptorSetLayout* _layout = nullptr;
    BufferList _buffers;
    TextureList _textures;
    SamplerList _samplers;

    bool _isDirty = false;
};

}