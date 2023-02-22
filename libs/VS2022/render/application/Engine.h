#pragma once

#include "BaseEngine.h"

#include <glm/glm.hpp>
#include <map>
#include <thread>
#include <chrono>

namespace ll
{
    
    class Device;
    class ProgramLib;
    class BuiltinResManager;

#define NANOSECONDS_60FPS      16666667L
#define NANOSECONDS_PER_SECOND 1000000000

class Engine : public BaseEngine
{
public:
    Engine();
    ~Engine() override;
    int32_t Init() override;
    int32_t Run() override;
    void Pause() override;
    void Resume() override;
    int Restart() override;
    void Close() override;
    void SetPreferredFramesPerSecond(int fps) override;
    uint32_t GetTotalFrames() const override;

    bool IsInited() const override { return _inited; }

private:
    void Destroy();
    void Tick();
    void DoRestart();

    bool _close{ false };
    bool _pause{ false };
    bool _resune{ false };
    int64_t _prefererredNanosecondsPerFrame{ NANOSECONDS_60FPS };
    uint32_t _totalFrames{ 0 };
    glm::vec2 _viewLogicalSize{ 0, 0 };
    bool _needRestart{ false };
    bool _inited{ false };

    //FileUtils* _fs{ nullptr };
    Device* _gfxDevice{ nullptr };

    ProgramLib* _programLib{ nullptr };
    BuiltinResManager* _builtinResManager{ nullptr };

    DISALLOW_COPY_MOVE_ASSIGN(Engine)
};

}