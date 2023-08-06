#pragma once

#include "BaseDispatchPass.h"

namespace OGL
{
class BRDFIntegrator : public BaseDispatchPass
{
public:
	using BaseDispatchPass::BaseDispatchPass;
	void Dispatch(Frame& frame) final;
};
}
