#pragma once

// Small hand-made graphs with KNOWN chromatic numbers, for testing the
// colouring algorithms without needing the random network generator.

#include "graph/interference_graph.hpp"

#include <random>
#include <vector>

namespace rf::test {

// n vertices, no edges. χ = 1.
inline InterferenceGraph makeEmpty(std::size_t n) {
    return InterferenceGraph(n);
}

// Complete graph K_n. χ = n.
inline InterferenceGraph makeComplete(std::size_t n) {
    InterferenceGraph g(n);
    for (VertexId u = 0; u < n; ++u)
        for (VertexId v = u + 1; v < n; ++v) g.addEdge(u, v);
    return g;
}

// Path 0-1-2-...-(n-1). χ = 2.
inline InterferenceGraph makePath(std::size_t n) {
    InterferenceGraph g(n);
    for (VertexId v = 0; v + 1 < n; ++v) g.addEdge(v, v + 1);
    return g;
}

// Cycle of length n. χ = 2 (n even) or 3 (n odd).
inline InterferenceGraph makeCycle(std::size_t n) {
    InterferenceGraph g = makePath(n);
    g.addEdge(n - 1, 0);
    return g;
}

// Crown graph: a_i = i, b_i = k + i, edge a_i - b_j whenever i != j. χ = 2.
inline InterferenceGraph makeCrown(std::size_t k) {
    InterferenceGraph g(2 * k);
    for (VertexId i = 0; i < k; ++i)
        for (VertexId j = 0; j < k; ++j)
            if (i != j) g.addEdge(i, k + j);
    return g;
}

// Worst order for the crown graph: a0, b0, a1, b1, ...
inline std::vector<VertexId> crownBadOrder(std::size_t k) {
    std::vector<VertexId> order;
    for (VertexId i = 0; i < k; ++i) {
        order.push_back(i);
        order.push_back(k + i);
    }
    return order;
}

// The 6-tower example: A..F = 0..5. χ = 3.
inline InterferenceGraph makeTowerExample() {
    InterferenceGraph g(6);
    g.addEdge(0, 1); g.addEdge(0, 3); g.addEdge(1, 2); g.addEdge(1, 3);
    g.addEdge(1, 4); g.addEdge(2, 4); g.addEdge(2, 5); g.addEdge(3, 4);
    return g;
}

// Random graph: each pair is an edge with probability p.
inline InterferenceGraph makeRandom(std::size_t n, double p, std::uint64_t seed) {
    InterferenceGraph g(n);
    std::mt19937_64 engine(seed);
    std::uniform_real_distribution<double> coin(0.0, 1.0);
    for (VertexId u = 0; u < n; ++u)
        for (VertexId v = u + 1; v < n; ++v)
            if (coin(engine) < p) g.addEdge(u, v);
    return g;
}

}
