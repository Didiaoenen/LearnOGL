#pragma once

#include <vector>

namespace ll
{

using MeshWeightsType = std::vector<float>;

using IBArray = std::variant<Uint8Array, Uint16Array, Uint32Array>;

}