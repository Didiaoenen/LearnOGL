#pragma once

namespace ll
{

enum class CSMLevel 
{
    LEVEL_1 = 1,
    LEVEL_2 = 2,
    LEVEL_3 = 3,
    LEVEL_4 = 4,
};

enum class PCFType 
{
    HARD = 0,
    SOFT = 1,
    SOFT_2X = 2,
    SOFT_4X = 3,
};

enum class CSMOptimizationMode 
{
    NONE = 1,
    REMOVE_DUPLICATES = 2,
    DISABLE_ROTATION_FIX = 3,
};


class Shadows
{
public:

};

}