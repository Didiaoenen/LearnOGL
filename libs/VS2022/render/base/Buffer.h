#pragma once

#include "Def_common.h"

namespace ll
{

class Buffer
{
public:
	Buffer();
	virtual ~Buffer();

	void Initialize(const BufferInfo& info);
	void Initialize(const BufferViewInfo& info);
	void Destroy();

    virtual void Update(const void* buffer, uint32_t size) = 0;

    inline void Update(const void* buffer) { Update(buffer, _size); }

    inline BufferUsage GetUsage() const { return _usage; }
    inline MemoryUsage GetMemUsage() const { return _memUsage; }
    inline uint32_t GetStride() const { return _stride; }
    inline uint32_t GetCount() const { return _count; }
    inline uint32_t GetSize() const { return _size; }
    inline BufferFlags GetFlags() const { return _flags; }
    inline bool IsBufferView() const { return _isBufferView; }

protected:
    virtual void DoInit(const BufferInfo& info) = 0;
    virtual void DoInit(const BufferViewInfo& info) = 0;
    virtual void DoDestroy() = 0;

    BufferUsage _usage = BufferUsageBit::NONE;
    MemoryUsage _memUsage = MemoryUsageBit::NONE;
    uint32_t _stride = 0U;
    uint32_t _count = 0U;
    uint32_t _size = 0U;
    uint32_t _offset = 0U;
    BufferFlags _flags = BufferFlagBit::NONE;
    bool _isBufferView = false;

};

}
