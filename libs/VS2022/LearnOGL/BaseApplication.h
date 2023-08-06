#pragma once

#include <vector>
#include <typeinfo> 

#include "IApplication.h"

#include "IGameLogic.h"
#include "ISceneManager.h"

namespace OGL
{
class BaseApplication : public IApplication
{
public:
	BaseApplication() = default;
	~BaseApplication() override = default;

	virtual bool Initialize();
	virtual void Finalize();

	virtual void Tick();

	virtual void* GetMainWindowHandler() override { return nullptr; }

	[[nodiscard]] const GfxConfiguration& GetConfiguration() const override { return mConfig; }

	[[nodiscard]] bool IsQuit() const override { return mQuit; }

	void RequestQuit() override { mQuit = true; }

	void RegisterRuntimeModule(IRuntimeModule* rmodule);

	template<typename T>
	T* GetModule(const type_info& type);

protected:
	bool mQuit{ false };
	GfxConfiguration mConfig;

	IGameLogic* mGameLogic{ nullptr };

private:
	std::vector<IRuntimeModule*> mRuntimeModules;
};

template<typename T>
inline T* BaseApplication::GetModule(const type_info& type)
{
	for (const auto& rmodule : mRuntimeModules)
	{
		if (typeid(rmodule) == type)
		{
			return static_cast<T*>(rmodule);
		}
	}

	return nullptr;
}
}

