#include "graph/interference_graph.hpp"

#include <algorithm>
#include <stdexcept>

namespace rf {

InterferenceGraph::InterferenceGraph(std::size_t vertices)
    : adjacencyList_(vertices), edgeCount_(0) {}

void InterferenceGraph::addEdge(VertexId u, VertexId v) {

    if (u >= vertexCount() || v >= vertexCount()) {
        throw std::out_of_range("Invalid vertex ID");
    }

    if (u == v) {
        throw std::invalid_argument("Self-loops are not allowed");
    }

    if (hasEdge(u, v)) {
        return;
    }

    adjacencyList_[u].push_back(v);
    adjacencyList_[v].push_back(u);

    ++edgeCount_;
}

bool InterferenceGraph::hasEdge(VertexId u, VertexId v) const {

    if (u >= vertexCount() || v >= vertexCount()) {
        throw std::out_of_range("Invalid vertex ID");
    }

    const auto& neighbors = adjacencyList_[u];

    return std::find(
        neighbors.begin(),
        neighbors.end(),
        v
    ) != neighbors.end();
}

const std::vector<VertexId>&
InterferenceGraph::getNeighbors(VertexId u) const {

    return adjacencyList_.at(u);
}

std::size_t InterferenceGraph::vertexCount() const {
    return adjacencyList_.size();
}

std::size_t InterferenceGraph::edgeCount() const {
    return edgeCount_;
}

bool InterferenceGraph::isValid() const {

    std::size_t countedEdges = 0;

    for (VertexId u = 0; u < vertexCount(); ++u) {

        for (VertexId v : adjacencyList_[u]) {

            if (v >= vertexCount() || u == v) {
                return false;
            }

            if (!hasEdge(v, u)) {
                return false;
            }

            ++countedEdges;
        }
    }

    return countedEdges == 2 * edgeCount_;
}

}