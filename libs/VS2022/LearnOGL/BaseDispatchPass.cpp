#include "BaseDispatchPass.h"

using namespace OGL;

void BaseDispatchPass::BeginPass([[maybe_unused]] Frame& frame)
{
	mGraphicsManager->BeginCompute();
}

void BaseDispatchPass::EndPass([[maybe_unused]] Frame& frame)
{
	mGraphicsManager->EndCompute();
}
