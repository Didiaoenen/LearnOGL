#pragma once

#include <string>

namespace ll
{

struct MovePair 
{
    MovePair(MovePair&& rhs) noexcept = default;
    MovePair(MovePair const& rhs) = delete;
    MovePair& operator=(MovePair&& rhs) = default;
    MovePair& operator=(MovePair const& rhs) = default;

    std::pmr::string source;
    std::pmr::string target;
    uint32_t           mipLevels{ 0xFFFFFFFF };
    uint32_t           numSlices{ 0xFFFFFFFF };
    uint32_t           targetMostDetailedMip{ 0 };
    uint32_t           targetFirstSlice{ 0 };
    uint32_t           targetPlaneSlice{ 0 };
};

struct CopyPair 
{
    CopyPair(CopyPair&& rhs) noexcept = default;
    CopyPair(CopyPair const& rhs) = delete;
    CopyPair& operator=(CopyPair&& rhs) = default;
    CopyPair& operator=(CopyPair const& rhs) = default;

    std::pmr::string source;
    std::pmr::string target;
    uint32_t           mipLevels{ 0xFFFFFFFF };
    uint32_t           numSlices{ 0xFFFFFFFF };
    uint32_t           sourceMostDetailedMip{ 0 };
    uint32_t           sourceFirstSlice{ 0 };
    uint32_t           sourcePlaneSlice{ 0 };
    uint32_t           targetMostDetailedMip{ 0 };
    uint32_t           targetFirstSlice{ 0 };
    uint32_t           targetPlaneSlice{ 0 };
};

}