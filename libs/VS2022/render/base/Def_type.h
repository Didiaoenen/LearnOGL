#pragma once

#include <cassert>
#include <unordered_map>

namespace ll
{

using index_t = int32_t;

#define Record std::unordered_map

#define CC_ENUM_CONVERSION_OPERATOR(T) \
    inline std::underlying_type<T>::type toNumber(const T v) { return static_cast<std::underlying_type<T>::type>(v); }

#define CC_ENUM_BITWISE_OPERATORS(T)                                                                                                                                           \
    inline bool operator!(const T v) { return !static_cast<std::underlying_type<T>::type>(v); }                                                                                \
    inline T operator~(const T v) { return static_cast<T>(~static_cast<std::underlying_type<T>::type>(v)); }                                                                   \
    inline bool operator||(const T lhs, const T rhs) { return (static_cast<std::underlying_type<T>::type>(lhs) || static_cast<std::underlying_type<T>::type>(rhs)); }          \
    inline bool operator&&(const T lhs, const T rhs) { return (static_cast<std::underlying_type<T>::type>(lhs) && static_cast<std::underlying_type<T>::type>(rhs)); }          \
    inline T operator|(const T lhs, const T rhs) { return static_cast<T>(static_cast<std::underlying_type<T>::type>(lhs) | static_cast<std::underlying_type<T>::type>(rhs)); } \
    inline T operator&(const T lhs, const T rhs) { return static_cast<T>(static_cast<std::underlying_type<T>::type>(lhs) & static_cast<std::underlying_type<T>::type>(rhs)); } \
    inline T operator^(const T lhs, const T rhs) { return static_cast<T>(static_cast<std::underlying_type<T>::type>(lhs) ^ static_cast<std::underlying_type<T>::type>(rhs)); } \
    inline T operator+(const T lhs, const T rhs) { return static_cast<T>(static_cast<std::underlying_type<T>::type>(lhs) + static_cast<std::underlying_type<T>::type>(rhs)); } \
    inline T operator+(const T lhs, bool rhs) { return static_cast<T>(static_cast<std::underlying_type<T>::type>(lhs) + rhs); }                                                \
    inline void operator|=(T &lhs, const T rhs) { lhs = static_cast<T>(static_cast<std::underlying_type<T>::type>(lhs) | static_cast<std::underlying_type<T>::type>(rhs)); }   \
    inline void operator&=(T &lhs, const T rhs) { lhs = static_cast<T>(static_cast<std::underlying_type<T>::type>(lhs) & static_cast<std::underlying_type<T>::type>(rhs)); }   \
    inline void operator^=(T &lhs, const T rhs) { lhs = static_cast<T>(static_cast<std::underlying_type<T>::type>(lhs) ^ static_cast<std::underlying_type<T>::type>(rhs)); }   \
    inline bool hasFlag(const T flags, const T flagToTest) {                                                                                                                   \
        using ValueType = std::underlying_type<T>::type;                                                                                                                       \
        assert((static_cast<ValueType>(flagToTest) & (static_cast<ValueType>(flagToTest) - 1)) == 0);                                                                       \
        return (static_cast<ValueType>(flags) & static_cast<ValueType>(flagToTest)) != 0;                                                                                      \
    }                                                                                                                                                                          \
    inline bool hasAnyFlags(const T flags, const T flagsToTest) {                                                                                                              \
        using ValueType = std::underlying_type<T>::type;                                                                                                                       \
        return (static_cast<ValueType>(flags) & static_cast<ValueType>(flagsToTest)) != 0;                                                                                     \
    }                                                                                                                                                                          \
    inline bool hasAllFlags(const T flags, const T flagsToTest) {                                                                                                              \
        using ValueType = std::underlying_type<T>::type;                                                                                                                       \
        return (static_cast<ValueType>(flags) & static_cast<ValueType>(flagsToTest)) == static_cast<ValueType>(flagsToTest);                                                   \
    }                                                                                                                                                                          \
    inline T addFlags(T &flags, const T flagsToAdd) {                                                                                                                          \
        flags |= flagsToAdd;                                                                                                                                                   \
        return flags;                                                                                                                                                          \
    }                                                                                                                                                                          \
    inline T removeFlags(T &flags, const T flagsToRemove) {                                                                                                                    \
        flags &= ~flagsToRemove;                                                                                                                                               \
        return flags;                                                                                                                                                          \
    }                                                                                                                                                                          \
    CC_ENUM_CONVERSION_OPERATOR(T)

}