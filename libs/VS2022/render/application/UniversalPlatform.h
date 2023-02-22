#pragma once

#include "ISystem.h"
#include "BasePlatform.h"

namespace ll
{

class UniversalPlatform : public BasePlatform
{
public:
    int32_t Run(int argc, char* argv[]) override;
    ISystem::OSType GetOSType() const override;

    void PollEvent() override;
    int32_t GetFps() const override;
    void SetFps(int32_t fps) override;

    void RunInPlatformThread(const ThreadCallback& task) override;

    virtual void RunTask();
    virtual void OnPause();
    virtual void OnResume();
    virtual void OnClose();
    virtual void OnDestroy();

private:
    ThreadCallback _mainTask{ nullptr };

    int32_t _fps{ 60 };
};

}