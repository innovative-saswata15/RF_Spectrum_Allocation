#include "coloring/greedy_coloring.hpp"

#include <stdexcept>

namespace rf {

// colors[v] : answer sheet, NO_COLOR = not coloured yet      (index = vertex)
// mark[c]   : scratchpad, mark[c] == v means colour c is     (index = COLOUR)
//             used by a neighbour of the vertex v being coloured now.
//             Storing v (a "timestamp") instead of true/false means the
//             array never needs resetting => O(n + m) total.
//             VertexId is unsigned, so -1 can't mean "nobody";
//             we use n instead (never a valid vertex id).
ColorAssignment GreedyColoring::color(
    const InterferenceGraph& graph,
    const std::vector<VertexId>& order
) {
    const std::size_t n = graph.vertexCount();

    if (order.size() != n) {
        throw std::invalid_argument("Order must contain every vertex once");
    }

    ColorAssignment colors(n, NO_COLOR);
    std::vector<VertexId> mark(n + 1, n);    // colours are always <= n-1

    for (VertexId v : order) {

        // The timestamp trick needs each vertex to appear only once.
        if (v >= n || colors[v] != NO_COLOR) {
            throw std::invalid_argument("Order must be a permutation of 0..n-1");
        }

        // 1. Block every colour used by an already-coloured neighbour.
        for (VertexId u : graph.getNeighbors(v)) {
            if (colors[u] != NO_COLOR) {
                mark[static_cast<std::size_t>(colors[u])] = v;
            }
        }

        // 2. Smallest colour not blocked for v (at most deg(v)+1 checks).
        std::size_t c = 0;
        while (mark[c] == v) {
            ++c;
        }

        colors[v] = static_cast<Color>(c);   // permanent decision
    }

    return colors;
}

}
