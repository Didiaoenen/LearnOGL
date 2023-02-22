#pragma once

#include "Ptr.h"
#include "Macros.h"
#include "Def_common.h"

#include "FrameBuffer.h"

#include <string>
#include <vector>
#include <optional>

namespace ll
{

    class Camera;
    class Device;

struct IRenderWindowInfo 
{
    std::optional<std::string> title;
    uint32_t width{ 0 };
    uint32_t height{ 0 };
    RenderPassInfo renderPassInfo;
    Swapchain* swapchain{ nullptr };
};

class RenderWindow
{
public:
    RenderWindow();
    virtual ~RenderWindow();

    bool Initialize(Device* device, IRenderWindowInfo& info);
    void Destroy();

    void Resize(uint32_t width, uint32_t height);
    void ExtractRenderCameras(std::vector<Camera*>& cameras);
    void AttachCamera(Camera* camera);
    void DetachCamera(Camera* camera);
    void ClearCameras();
    void SortCameras();
    inline uint32_t GetWidth() const { return _width; }
    inline uint32_t GetHeight() const { return _height; }
    inline Swapchain* GetSwapchain() { return _swapchain; }
    inline FrameBuffer* GetFramebuffer() const { return _frameBuffer.get(); }
    inline const std::vector<IntrusivePtr<Camera>>& GetCameras() const { return _cameras; }

private:
    uint32_t _width{ 1 };
    uint32_t _height{ 1 };
    Swapchain* _swapchain{ nullptr };
    std::string _title;
    IntrusivePtr<RenderPass> _renderPass;
    IntrusivePtr<Texture> _depthStencilTexture;
    IntrusivePtr<FrameBuffer> _frameBuffer;
    std::vector<IntrusivePtr<Camera>> _cameras;
    std::vector<Texture*> _colorTextures;

    CC_DISALLOW_COPY_MOVE_ASSIGN(RenderWindow)

};

}