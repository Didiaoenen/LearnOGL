#pragma once

#include "ISystemWindow.h"
#include "IEventDispatch.h"

#include <memory>

namespace ll
{

class SystemWindow : public ISystemWindow
{
public:
    explicit SystemWindow(IEventDispatch* delegate);
    virtual ~SystemWindow();

    int Init();
    void PollEvent(bool* quit);
    void SwapWindow();

    bool _CreateWindow(const char* title, int w, int h, int flags) override;
    bool _CreateWindow(const char* title, int x, int y, int w, int h, int flags) override;
    void CloseWindow() override;
    uintptr_t GetWindowHandle() const override;
    Size GetViewSize() const override;
    
    void SetViewSize(uint32_t width, uint32_t height) override 
    {
        _width = width;
        _height = height;
    }

    void SetCursorEnabled(bool value) override;

private:
    int _width{ 0 };
    int _height{ 0 };
    //std::unique_ptr<SDLHelper> _sdl;
};

}