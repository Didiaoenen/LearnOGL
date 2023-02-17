#pragma once

#include "Application.h"
#include "GlobalDSManager.h"

namespace ll
{

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
};

}