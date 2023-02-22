#pragma once

#include "../base/Ptr.h"

#include "../base/Texture.h"

#include <map>

namespace ll
{

    class Light;
    class Buffer;
    class Device;
    class Sampler;
    class DescriptorSet;
    class DescriptorSetLayout;


class GlobalDSManager
{
public:
    GlobalDSManager() = default;
    ~GlobalDSManager() = default;

    inline Sampler* GetLinearSampler() const { return _linearSampler; }
    inline Sampler* GetPointSampler() const { return _pointSampler; }
    inline DescriptorSetLayout* GetDescriptorSetLayout() const { return _descriptorSetLayout; }
    inline DescriptorSet* GetGlobalDescriptorSet() const { return _globalDescriptorSet; }

    void Activate(Device* device);
    void BindBuffer(uint32_t binding, Buffer* buffer);
    void BindTexture(uint32_t binding, Texture* texture);
    void BindSampler(uint32_t binding, Sampler* sampler);
    void Update();
    DescriptorSet* GetOrCreateDescriptorSet(const Light* light);
    void Destroy();

    static void SetDescriptorSetLayout();

private:
    Device* _device{ nullptr };

    Sampler* _linearSampler{ nullptr };
    Sampler* _pointSampler{ nullptr };

    IntrusivePtr<Texture> _defaultTexture;

    IntrusivePtr<DescriptorSetLayout> _descriptorSetLayout;
    IntrusivePtr<DescriptorSet> _globalDescriptorSet;
    std::vector<IntrusivePtr<Buffer>> _shadowUBOs;
    std::map<const Light*, IntrusivePtr<DescriptorSet>> _descriptorSetMap;
};

}