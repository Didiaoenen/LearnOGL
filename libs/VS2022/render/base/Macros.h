#pragma once

#define CC_DISALLOW_ASSIGN(TypeName)                \
    TypeName &operator=(const TypeName &) = delete; \
    TypeName &operator=(TypeName &&) = delete;

#define CC_DISALLOW_COPY_MOVE_ASSIGN(TypeName) \
    TypeName(const TypeName &) = delete;       \
    TypeName(TypeName &&) = delete;            \
    CC_DISALLOW_ASSIGN(TypeName)