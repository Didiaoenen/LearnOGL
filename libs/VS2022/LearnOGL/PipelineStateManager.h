#pragma once

#include <map>

#include "IPipelineStateManager.h"

using namespace std;

namespace OGL
{
class PipelineStateManager : public IPipelineStateManager
{
public:
	~PipelineStateManager() override;

	bool Initialize() override;
	void Finalize() override;
	void Tick() override {}

	void RegisterPipelineState(PipelineState& pipelineState) override;
	void UnregisterPipelineState(PipelineState& pipelineState) override;
	
	void Clear() override;

	const shared_ptr<PipelineState> GetPipelineState(string name) const final;
	
protected:
	virtual bool InitializePipelineState(PipelineState** ppPipelineState) { return true; }

	virtual void DestroyPipelineState(PipelineState& pipelineState) {}

protected:
	map<std::string, shared_ptr<PipelineState>> mPipelineStates;
};
}
