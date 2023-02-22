#pragma once

#include "../base/DescriptorSetLayout.h"

namespace ll
{

    struct GLES2GPUDescriptorSetLayout;

class glDescriptorSetLayout final : public DescriptorSetLayout
{
public:
    glDescriptorSetLayout();
    ~glDescriptorSetLayout() override;

    inline GLES2GPUDescriptorSetLayout* GpuDescriptorSetLayout() const { return _gpuDescriptorSetLayout; }

protected:
    void DoInit(const DescriptorSetLayoutInfo& info) override;
    void DoDestroy() override;

    GLES2GPUDescriptorSetLayout* _gpuDescriptorSetLayout = nullptr;
};

}