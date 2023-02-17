#pragma once

#include "DescriptorSet.h"

namespace ll
{

    struct GPUDescriptorSet;

class glDescriptorSet final : public DescriptorSet
{
public:
    glDescriptorSet();
    ~glDescriptorSet() override;

    void Update() override;
    void ForceUpdate() override;

    inline GPUDescriptorSet* GpuDescriptorSet() const { return _gpuDescriptorSet; }

protected:
    void DoInit(const DescriptorSetInfo& info) override;
    void DoDestroy() override;

    GPUDescriptorSet* _gpuDescriptorSet = nullptr;
};

}