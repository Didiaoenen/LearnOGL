#include "Swapchain.h"

ll::Swapchain::Swapchain()
{
}

ll::Swapchain::~Swapchain() = default;

void ll::Swapchain::Initialize(const SwapchainInfo& info)
{
    _windowHandle = info.windowHandle;
    _vsyncMode = info.vsyncMode;

    DoInit(info);
}