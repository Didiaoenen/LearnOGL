#pragma once

#include "OSInterface.h"

#include <glm/glm.hpp>
#include <string>

namespace ll
{

class ISystemWindow : public OSInterface
{
public:
    using WindowFlags = enum 
    {
        CC_WINDOW_FULLSCREEN = 0x00000001,
        CC_WINDOW_OPENGL = 0x00000002,
        CC_WINDOW_SHOWN = 0x00000004,
        CC_WINDOW_HIDDEN = 0x00000008,
        CC_WINDOW_BORDERLESS = 0x00000010,
        CC_WINDOW_RESIZABLE = 0x00000020,
        CC_WINDOW_MINIMIZED = 0x00000040,
        CC_WINDOW_MAXIMIZED = 0x00000080,
        CC_WINDOW_INPUT_GRABBED = 0x00000100,
        CC_WINDOW_INPUT_FOCUS = 0x00000200,
        CC_WINDOW_MOUSE_FOCUS = 0x00000400,
        CC_WINDOW_FULLSCREEN_DESKTOP = (CC_WINDOW_FULLSCREEN | 0x00001000),
        CC_WINDOW_FOREIGN = 0x00000800,
        CC_WINDOW_ALLOW_HIGHDPI = 0x00002000, 
        CC_WINDOW_MOUSE_CAPTURE = 0x00004000,
        CC_WINDOW_ALWAYS_ON_TOP = 0x00008000,
        CC_WINDOW_SKIP_TASKBAR = 0x00010000,
        CC_WINDOW_UTILITY = 0x00020000,
        CC_WINDOW_TOOLTIP = 0x00040000,
        CC_WINDOW_POPUP_MENU = 0x00080000,
        CC_WINDOW_VULKAN = 0x10000000
    };

    virtual bool _CreateWindow(const char* title, int x, int y, int w, int h, int flags) 
    {
        return true;
    }

    virtual bool _CreateWindow(const char* title, int w, int h, int flags) 
    {
        return true;
    }

    virtual void CloseWindow() {}
    virtual uintptr_t GetWindowHandle() const = 0;
    virtual glm::vec2 GetViewSize() const = 0;
    virtual void SetViewSize(uint32_t width, uint32_t height) {}
    virtual void SetCursorEnabled(bool value) = 0;
};

}