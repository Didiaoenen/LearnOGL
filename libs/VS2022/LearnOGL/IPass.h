#pragma once

#include "FrameStructure.h"

namespace OGL
{
class IPass
{
public:
	virtual ~IPass() = default;

	virtual void BeginPass(Frame& frame) = 0;
	virtual void EndPass(Frame& frame) = 0;
};
}
