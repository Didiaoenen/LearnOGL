#pragma once

#include "BasePlatform.h"

int main(int argc, char* argv[])
{
    do
    {
        ll::BasePlatform* platform = ll::BasePlatform::GetPlatform();
        if (platform->Init())
        {
            return -1;
        }
        return platform->Run(argc, argv);
    } while (0);

    return 0;
}