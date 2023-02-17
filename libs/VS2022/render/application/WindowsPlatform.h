#pragma once

#include "UniversalPlatform.h"

#include <memory>

namespace ll
{

class SystemWindow;

class WindowsPlatform : public UniversalPlatform
{
public:
    WindowsPlatform();
    ~WindowsPlatform() override;
    int32_t Init() override;

    int32_t Loop() override;

private:
    std::shared_ptr<SystemWindow> _window{ nullptr };
    bool _quit{ false };
};

}