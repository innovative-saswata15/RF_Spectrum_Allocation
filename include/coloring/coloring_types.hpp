#pragma once

#include <vector>

namespace rf {

// A colour = a channel number: 0, 1, 2, ...
using Color = int;

// "Not coloured yet". Colours are never negative, so -1 is a safe sentinel.
constexpr Color NO_COLOR = -1;

// colors[v] = channel given to transmitter v (index = VertexId).
using ColorAssignment = std::vector<Color>;

}
