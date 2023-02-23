#include "Game.h"

#include "../core/Root.h"
#include "../base/Director.h"
#include "../base/DeviceManager.h"
#include "../pipeline/GlobalDSManager.h"

ll::Game::Game()
{
}

ll::Game::Game(int width, int height)
{
}

ll::Game::~Game()
{
}

int ll::Game::Init()
{
    ll::GlobalDSManager::SetDescriptorSetLayout();

    auto ret = Application::Init();
    if (ret != 0)
    {
        return ret;
    }

    DeviceInfo info;
    DeviceManager::Create(info);

    _director = new Director();
    _director->Init();

    _director->GetRoot()->SetRenderPipeline();

    return 0;
}

void ll::Game::OnPause()
{
}

void ll::Game::OnResume()
{
}

void ll::Game::OnClose()
{
}