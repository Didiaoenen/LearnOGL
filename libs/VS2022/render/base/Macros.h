#pragma once

#define DISALLOW_ASSIGN(TypeName)                \
    TypeName &operator=(const TypeName &) = delete; \
    TypeName &operator=(TypeName &&) = delete;

#define DISALLOW_COPY_MOVE_ASSIGN(TypeName) \
    TypeName(const TypeName &) = delete;       \
    TypeName(TypeName &&) = delete;            \
    DISALLOW_ASSIGN(TypeName)