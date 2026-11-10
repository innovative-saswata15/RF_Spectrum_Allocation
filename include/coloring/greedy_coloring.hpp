#pragma once

#include "coloring/coloring_types.hpp"
#include "graph/interference_graph.hpp"

#include <vector>

namespace rf {

class GreedyColoring {
public:
    // Visit vertices in `order`; give each the smallest colour not used by
    // its already-coloured neighbours. `order` must contain every vertex
    // exactly once. Time O(n + m), extra space O(n).
    static ColorAssignment color(
        const InterferenceGraph& graph,
        const std::vector<VertexId>& order
    );
};

}
