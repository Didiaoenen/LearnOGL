#include "BaseApplication.h"

using namespace OGL;

bool BaseApplication::Initialize()
{
	for (const auto& rmodule : mRuntimeModules)
	{
		if (!rmodule->Initialize())
		{
			return false;
		}
	}

    return true;
}

void BaseApplication::Finalize()
{
	for (const auto& rmodule : mRuntimeModules)
	{
		rmodule->Finalize();
	}

	mRuntimeModules.clear();
}

void BaseApplication::Tick()
{
	for (const auto& rmodule : mRuntimeModules)
	{
		rmodule->Tick();
	}
}

void BaseApplication::RegisterRuntimeModule(IRuntimeModule* rmodule)
{
	rmodule->SetApp(this);
	mRuntimeModules.push_back(rmodule);
}
