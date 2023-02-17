#pragma once

#include "Macros.h"

#include <memory>

namespace ll
{

class OSInterface
{
public:
    explicit OSInterface() = default;
    virtual ~OSInterface() = default;

    using Ptr = std::shared_ptr<OSInterface>;

private:
    CC_DISALLOW_COPY_MOVE_ASSIGN(OSInterface)
};

}