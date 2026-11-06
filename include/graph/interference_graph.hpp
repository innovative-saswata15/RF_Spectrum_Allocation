#pragma once

#include "network/transmitter.hpp"

#include <vector>

namespace rf {

class InterferenceGraph {
private:
    std::vector<std::vector<VertexId>> adjacencyList_;
    std::size_t edgeCount_;

public:
    explicit InterferenceGraph(std::size_t vertices);

    void addEdge(VertexId u, VertexId v);

    bool hasEdge(VertexId u, VertexId v) const;

    const std::vector<VertexId>& getNeighbors(VertexId u) const;

    std::size_t vertexCount() const;

    std::size_t edgeCount() const;

    bool isValid() const;
};

}