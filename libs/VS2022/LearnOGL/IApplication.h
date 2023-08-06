#pragma once

#include "GfxConfiguration.h"

namespace OGL
{
class IApplication
{
public:
	virtual ~IApplication() = default;

	[[nodiscard]] virtual bool IsQuit() const = 0;
	virtual void RequestQuit() = 0;

	virtual void* GetMainWindowHandler() = 0;

	[[nodiscard]] virtual const GfxConfiguration& GetConfiguration() const = 0;
};
}
