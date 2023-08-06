#pragma once

#include "IApplication.h"

namespace OGL
{
class IRuntimeModule
{
public:
	IRuntimeModule() = default;
	virtual ~IRuntimeModule() = default;

	virtual bool Initialize() = 0;
	virtual void Finalize() = 0;
	
	virtual void Tick() = 0;

	void SetApp(IApplication* pApp) { mApp = pApp; }

protected:
	IApplication* mApp;
};
}

