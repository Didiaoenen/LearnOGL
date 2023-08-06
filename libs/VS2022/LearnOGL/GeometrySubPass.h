#pragma once

#include "BaseSubPass.h"

namespace OGL
{
class GeometrySubPass : public BaseSubPass
{
public:
	using BaseSubPass::BaseSubPass;
	void Draw(Frame& frame) final;
};
}