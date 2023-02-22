#pragma once

#include <cmath>

namespace ll
{

inline bool IsEqualF(float lhs, float rhs, float precision = 0.000001F) 
{
    return (std::fabs(lhs - rhs) < precision);
}

inline bool IsNotEqualF(float lhs, float rhs, float precision = 0.000001F) 
{
    return (std::fabs(lhs - rhs) > precision);
}

inline bool IsNotZeroF(float v, float precision = 0.000001F) 
{
    return (std::fabs(v) > precision);
}

}