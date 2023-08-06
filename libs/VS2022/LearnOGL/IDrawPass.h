#pragma once

#include "IPass.h"

namespace OGL
{
class IDrawPass : public IPass
{
public:
	virtual void Draw(Frame& frame) = 0;
};
}