#pragma once

#include "../base//Macros.h"

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
    DISALLOW_COPY_MOVE_ASSIGN(OSInterface)
};

}