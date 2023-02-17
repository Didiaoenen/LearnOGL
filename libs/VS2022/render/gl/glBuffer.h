#pragma once

#include "Def_common.h"
#include "glCommands.h"

namespace ll
{

	struct GPUBuffer;
	struct GPUBufferView;

class glBuffer final : public Buffer
{
public:
	glBuffer();
	~glBuffer() override;

	void Update(const void* buffer, uint32_t size) override;

	inline GPUBuffer* GpuBuffer() const { return _gpuBuffer; }
	inline GPUBufferView* GpuBufferView() const { return _gpuBufferView; }

protected:
	void DoInit(const BufferInfo& info) override;
	void DoInit(const BufferViewInfo& info) override;
	void DoDestroy() override;

	GPUBuffer* _gpuBuffer = nullptr;
	GPUBufferView* _gpuBufferView = nullptr;
};

}