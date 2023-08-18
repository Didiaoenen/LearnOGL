#pragma once

#include <string>

#include "RefCounts.h"

namespace OGL
{
class OGL_Asset : public RefCounts
{
public:
	OGL_Asset() = default;
	virtual ~OGL_Asset() = default;

public:
	std::string mFileName{};
	bool mLoaded{ false };
};
}

