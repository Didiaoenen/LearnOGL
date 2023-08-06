#pragma once

#include "BaseDrawPass.h"

namespace OGL
{
class ShadowMapPass : public BaseDrawPass
{
public:
	using BaseDrawPass::BaseDrawPass;
	~ShadowMapPass() override = default;

	void Draw(Frame& frame) final;

	void BeginPass(Frame& frame) override {}
	void EndPass(Frame& frame) override {}
};
}

