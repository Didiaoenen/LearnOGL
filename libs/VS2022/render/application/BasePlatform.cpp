#include "BasePlatform.h"

#include "WindowsPlatform.h"

ll::BasePlatform* ll::BasePlatform::_currentPlatform = nullptr;

ll::BasePlatform::BasePlatform()
{
	_currentPlatform = this;
}

ll::BasePlatform::~BasePlatform()
{
}

ll::BasePlatform* ll::BasePlatform::GetPlatform()
{
    if (_currentPlatform) 
    {
        return _currentPlatform;
    }
    CreateDefaultPlatform();
    return _currentPlatform;
}

ll::BasePlatform* ll::BasePlatform::CreateDefaultPlatform()
{
	static WindowsPlatform platform;
	return &platform;
}
