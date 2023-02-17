#include "Game.h"

#include "ApplicationManager.h"

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

CC_REGISTER_APPLICATION(ll::Game)