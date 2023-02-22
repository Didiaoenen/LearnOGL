#pragma once

#include "../base/Swapchain.h"

namespace ll
{

    struct GPUSwapchain;

class glSwapchain final : public Swapchain
{
public:
	glSwapchain();
	~glSwapchain() override;

	inline GPUSwapchain* GpuSwapchain() const { return _gpuSwapchain; }

private:
    void DoInit(const SwapchainInfo& info) override;
    void DoDestroy() override;
    void DoDestroySurface() override;
    void DoCreateSurface(void* windowHandle) override;

    GPUSwapchain* _gpuSwapchain{ nullptr };

};

}

