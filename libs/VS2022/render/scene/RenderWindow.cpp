#include "RenderWindow.h"

ll::RenderWindow::RenderWindow()
{
}

ll::RenderWindow::~RenderWindow()
{
}

bool ll::RenderWindow::Initialize(Device* device, IRenderWindowInfo& info)
{
    return false;
}

void ll::RenderWindow::Destroy()
{
}

void ll::RenderWindow::Resize(uint32_t width, uint32_t height)
{
}

void ll::RenderWindow::ExtractRenderCameras(std::vector<Camera*>& cameras)
{
}

void ll::RenderWindow::AttachCamera(Camera* camera)
{
}

void ll::RenderWindow::DetachCamera(Camera* camera)
{
}

void ll::RenderWindow::ClearCameras()
{
}

void ll::RenderWindow::SortCameras()
{
}
