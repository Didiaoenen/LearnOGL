#include "Buffer.h"

ll::Buffer::Buffer()
{
}

ll::Buffer::~Buffer()
{
}

void ll::Buffer::Initialize(const BufferInfo& info)
{
    _usage = info.usage;
    _memUsage = info.memUsage;
    _size = info.size;
    _flags = info.flags;
    _stride = std::max(info.stride, 1U);
    _count = _size / _stride;

    DoInit(info);
}

void ll::Buffer::Initialize(const BufferViewInfo& info)
{
    _usage = info.buffer->GetUsage();
    _memUsage = info.buffer->GetMemUsage();
    _flags = info.buffer->GetFlags();
    _offset = info.offset;
    _size = _stride = info.range;
    _count = 1U;
    _isBufferView = true;

    DoInit(info);
}

void ll::Buffer::Destroy()
{
}
