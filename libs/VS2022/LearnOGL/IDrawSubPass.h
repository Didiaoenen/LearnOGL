#pragma once

#include "ISubPass.h"
#include "FrameStructure.h"

namespace OGL
{
class IDrawSubPass : public ISubPass
{
public:
	virtual void Draw(Frame& frame) = 0;
};
}