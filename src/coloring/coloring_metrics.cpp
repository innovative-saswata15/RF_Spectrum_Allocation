#include "coloring/coloring_metrics.hpp"

#include <algorithm>
#include <vector>

namespace rf {

std::size_t ColoringMetrics::conflicts(
    const InterferenceGraph& graph,
    const ColorAssignment& colors
) {
    std::size_t count = 0;

    for (VertexId v = 0; v < graph.vertexCount(); ++v) {
        for (VertexId u : graph.getNeighbors(v)) {
            // u > v: count each undirected edge once, not twice.
            if (u > v && colors[v] != NO_COLOR && colors[u] == colors[v]) {
                ++count;
            }
        }
    }
    return count;
}

std::size_t ColoringMetrics::colorsUsed(const ColorAssignment& colors) {
    std::vector<bool> seen(colors.size() + 1, false);
    std::size_t distinct = 0;

    for (Color c : colors) {
        if (c == NO_COLOR) continue;
        auto index = static_cast<std::size_t>(c);
        if (index < seen.size() && !seen[index]) {
            seen[index] = true;
            ++distinct;
        }
    }
    return distinct;
}

bool ColoringMetrics::allColored(const ColorAssignment& colors) {
    return std::none_of(colors.begin(), colors.end(),
                        [](Color c) { return c == NO_COLOR; });
}

std::size_t ColoringMetrics::maxDegree(const InterferenceGraph& graph) {
    std::size_t delta = 0;
    for (VertexId v = 0; v < graph.vertexCount(); ++v) {
        delta = std::max(delta, graph.getNeighbors(v).size());
    }
    return delta;
}

}
