#include "Application.h"

ll::Application::Application()
{
    _engine = BaseEngine::CreateEngine();
    _systemWindow = _engine->GetInterface<ISystemWindow>();
}

ll::Application::~Application()
{
}

int32_t ll::Application::Init()
{
    if (_engine->Init()) 
    {
        return -1;
    }

    return 0;
}

int32_t ll::Application::Run(int argc, const char** argv)
{
    return _engine->Run();
}

void ll::Application::Pause()
{
    _engine->Pause();
}

void ll::Application::Resume()
{
    _engine->Resume();
}

void ll::Application::Restart()
{
    _engine->Restart();
}

void ll::Application::Close()
{
}

ll::BaseEngine::Ptr ll::Application::GetEngine() const
{
    return _engine;
}

void ll::Application::OnStart()
{
}

void ll::Application::OnPause()
{
}

void ll::Application::OnResume()
{
}

void ll::Application::OnClose()
{
    _engine->Close();
}

void ll::Application::CreateWindow(const char* title, int32_t x, int32_t y, int32_t w, int32_t h, int32_t flags)
{
}

void ll::Application::CreateWindow(const char* title, int32_t w, int32_t h, int32_t flags)
{
}
