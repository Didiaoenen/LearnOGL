#include "glBuffer.h"

#include "glDevice.h"
#include "glCommands.h"

ll::glBuffer::glBuffer()
{
}

ll::glBuffer::~glBuffer()
{
}

void ll::glBuffer::Update(const void* buffer, uint32_t size)
{
    cmdFuncUpdateBuffer(ll::glDevice::GetInstance(), _gpuBuffer, buffer, 0U, size);
}

void ll::glBuffer::DoInit(const BufferInfo& info)
{
    _gpuBuffer = new GPUBuffer;
    _gpuBuffer->usage = _usage;
    _gpuBuffer->memUsage = _memUsage;
    _gpuBuffer->size = _size;
    _gpuBuffer->stride = _stride;
    _gpuBuffer->count = _count;

    if (hasFlag(_usage, BufferUsageBit::INDIRECT)) 
    {
        _gpuBuffer->indirects.resize(_count);
    }

    cmdFuncCreateBuffer(ll::glDevice::GetInstance(), _gpuBuffer);
    ll::glDevice::GetInstance()->GetMemoryStatus().bufferSize += _size;
}

void ll::glBuffer::DoInit(const BufferViewInfo& info)
{
    auto* buffer = static_cast<glBuffer*>(info.buffer);
    _gpuBufferView = new GPUBufferView;
    _gpuBufferView->gpuBuffer = buffer->GpuBuffer();
    _gpuBufferView->range = _size;
    _gpuBufferView->offset = info.offset;
}

void ll::glBuffer::DoDestroy()
{
}
