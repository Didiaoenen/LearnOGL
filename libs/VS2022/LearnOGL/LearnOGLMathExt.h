#pragma once

#include <math.h>

static bool VecCloseEnough(const float fCandidate, const float fCompare, const float fEpsilon)
{
    return (fabs(fCandidate - fCompare) < fEpsilon);
}

static bool VecCloseEnough(const double dCandidate, const double dCompare, const double dEpsilon)
{
    return (fabs(dCandidate - dCompare) < dEpsilon);
}