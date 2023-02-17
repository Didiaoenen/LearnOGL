#include "ApplicationManager.h"

ll::ApplicationManager* ll::ApplicationManager::GetInstance()
{
	static ApplicationManager mgr;
	return &mgr;
}

void ll::ApplicationManager::ReleseAllApplications()
{
	_apps.clear();
}

ll::ApplicationManager::ApplicationPtr ll::ApplicationManager::GetCurrentApp() const
{
	if (_currentApp.expired()) 
	{
		return nullptr;
	}
	return _currentApp.lock();
}

ll::ApplicationManager::ApplicationPtr ll::ApplicationManager::GetCurrentAppSafe() const
{
	return _currentApp.lock();
}
