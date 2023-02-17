#include "BaseEngine.h"

#include "Engine.h"

ll::BaseEngine::~BaseEngine()
{
}

ll::BaseEngine::Ptr ll::BaseEngine::CreateEngine()
{
    return std::make_shared<Engine>();
}
