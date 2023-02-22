#include "SystemWindow.h"

ll::SystemWindow::SystemWindow(ll::IEventDispatch* delegate)
{
}

ll::SystemWindow::~SystemWindow()
{
}

int ll::SystemWindow::Init()
{
    return 0;
}

void ll::SystemWindow::PollEvent(bool* quit)
{
}

void ll::SystemWindow::SwapWindow()
{
}

bool ll::SystemWindow::_CreateWindow(const char* title, int w, int h, int flags)
{
    return false;
}

bool ll::SystemWindow::_CreateWindow(const char* title, int x, int y, int w, int h, int flags)
{
    return false;
}

void ll::SystemWindow::CloseWindow()
{
}

uintptr_t ll::SystemWindow::GetWindowHandle() const
{
    return uintptr_t();
}

glm::vec2 ll::SystemWindow::GetViewSize() const
{
    return glm::vec2();
}

void ll::SystemWindow::SetCursorEnabled(bool value)
{
}
