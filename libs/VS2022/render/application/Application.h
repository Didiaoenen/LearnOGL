#pragma once

#include "BaseApplication.h"

#include <string>

namespace ll
{

    class ISystemWindow;

class Application : public BaseApplication
{
public:
    Application();
    ~Application() override;

    int32_t Init() override;
    int32_t Run(int argc, const char** argv) override;
    void Pause() override;
    void Resume() override;
    void Restart() override;
    void Close() override;
    BaseEngine::Ptr GetEngine() const override;

    virtual void OnStart();
    virtual void OnPause();
    virtual void OnResume();
    virtual void OnClose();

    virtual void CreateWindow(const char* title, int32_t x, int32_t y, int32_t w, int32_t h, int32_t flags);
    virtual void CreateWindow(const char* title, int32_t w, int32_t h, int32_t flags);

private:
    ISystemWindow* _systemWindow{ nullptr };
    BaseEngine::Ptr _engine{ nullptr };
};

}