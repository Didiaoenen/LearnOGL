#pragma once

#include "Application.h"

#include "ApplicationManager.h"

namespace ll
{

    class Director;

class Game : public Application
{
public:
    Game();
    Game(int width, int height);
    ~Game();

    int Init() override;
    void OnPause() override;
    void OnResume() override;
    void OnClose() override;

private:
    Director* _director{ nullptr };

};

REGISTER_APPLICATION(ll::Game)

}