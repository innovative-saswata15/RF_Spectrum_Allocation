#pragma once

#include "graph/interference_graph.hpp"

#include <cstdint>
#include <vector>

namespace rf {

// Different visiting orders for Greedy colouring.
class VertexOrder {
public:
    // 0, 1, 2, ..., n-1
    static std::vector<VertexId> natural(std::size_t n);

    // Welsh–Powell: largest degree first, ties broken by smaller id.
    static std::vector<VertexId> largestDegreeFirst(
        const InterferenceGraph& graph
    );

    // Random permutation; same seed => same order (reproducible).
    static std::vector<VertexId> random(std::size_t n, std::uint64_t seed);
};

}
