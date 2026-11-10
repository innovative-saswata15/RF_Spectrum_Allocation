#pragma once

#include "coloring/coloring_types.hpp"
#include "graph/interference_graph.hpp"

#include <cstddef>

namespace rf {

// Measurements on a colouring (used by tests and by Member 3's benchmarks).
class ColoringMetrics {
public:
    // Edges whose two ends share a colour (0 = no interference).
    static std::size_t conflicts(
        const InterferenceGraph& graph,
        const ColorAssignment& colors
    );

    // Number of distinct channels actually used.
    static std::size_t colorsUsed(const ColorAssignment& colors);

    // True if every vertex received a colour.
    static bool allColored(const ColorAssignment& colors);

    // Maximum degree Δ (Greedy never uses more than Δ + 1 colours).
    static std::size_t maxDegree(const InterferenceGraph& graph);
};

}
