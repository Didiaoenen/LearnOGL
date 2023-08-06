#pragma once

#include "IPass.h"

namespace OGL
{
class IDispatchPass : public IPass
{
public:
	virtual void Dispatch(Frame& frame) = 0;

};
}
