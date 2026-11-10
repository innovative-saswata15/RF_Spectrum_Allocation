#include "coloring/vertex_order.hpp"

#include <algorithm>
#include <numeric>
#include <random>

namespace rf {

std::vector<VertexId> VertexOrder::natural(std::size_t n) {
    std::vector<VertexId> order(n);
    std::iota(order.begin(), order.end(), VertexId{0});   // 0, 1, ..., n-1
    return order;
}

std::vector<VertexId> VertexOrder::largestDegreeFirst(
    const InterferenceGraph& graph
) {
    std::vector<VertexId> order = natural(graph.vertexCount());

    // stable_sort keeps equal-degree vertices in id order (deterministic).
    std::stable_sort(order.begin(), order.end(),
        [&](VertexId a, VertexId b) {
            return graph.getNeighbors(a).size() > graph.getNeighbors(b).size();
        });

    return order;
}

std::vector<VertexId> VertexOrder::random(std::size_t n, std::uint64_t seed) {
    std::vector<VertexId> order = natural(n);
    std::mt19937_64 engine(seed);
    std::shuffle(order.begin(), order.end(), engine);
    return order;
}

}
