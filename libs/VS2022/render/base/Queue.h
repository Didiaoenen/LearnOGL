#pragma once

#include "Object.h"

namespace ll
{

class Queue : public Object
{
public:
    Queue();
    ~Queue() override;

    void Initialize(const QueueInfo& info);
    void Destroy();

    virtual void Submit(CommandBuffer* const* cmdBuffs, uint32_t count) = 0;
    inline void Submit(const CommandBufferList& cmdBuffs) { Submit(cmdBuffs.data(), uint32_t(cmdBuffs.size())); }
    inline QueueType GetType() const { return _type; }

protected:
    virtual void DoInit(const QueueInfo& info) = 0;
    virtual void DoDestroy() = 0;

    QueueType _type = QueueType::GRAPHICS;
};

}