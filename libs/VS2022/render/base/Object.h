#pragma once

#include "Def.h"

namespace ll
{

class Object
{
public:
    explicit Object(ObjectType type);
    virtual ~Object() = default;

    inline ObjectType GetObjectType() const { return _objectType; }
    inline uint32_t GetObjectID() const { return _objectID; }
    inline uint32_t GetTypedID() const { return _typedID; }

protected:
    template <typename T>
    static uint32_t GenerateObjectID() noexcept 
    {
        static uint32_t generator = 1 << 16;
        return ++generator;
    }

    ObjectType _objectType = ObjectType::UNKNOWN;
    uint32_t _objectID = 0U;

    uint32_t _typedID = 0U;
};

}