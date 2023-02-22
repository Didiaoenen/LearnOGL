#include "Game.h"

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
    //ll::GlobalDSManager::SetDescriptorSetLayout();



    auto ret = Application::Init();
    if (ret != 0)
    {
        return ret;
    }

    //DeviceManager::Create({});

    //_director = new Director();
    //_director->Init();

    //_director->GetRoot()->SetRenderPipeline();

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