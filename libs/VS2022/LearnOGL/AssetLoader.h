#pragma once

#include "IAssetLoader.h"

namespace OGL
{
class AssetLoader : public IAssetLoader
{
public:
	AssetLoader() = default;
	~AssetLoader() override = default;
};
}

