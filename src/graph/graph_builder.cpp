#include "graph/graph_builder.hpp"

namespace rf {

InterferenceGraph GraphBuilder::build(
    const Network& network,
    const InterferenceModel& model
) {

    std::size_t n = network.size();

    InterferenceGraph graph(n);

    const auto& transmitters = network.getTransmitters();

    for (VertexId i = 0; i < n; ++i) {

        for (VertexId j = i + 1; j < n; ++j) {

            if (model.interferes(
                    transmitters[i],
                    transmitters[j]
                )) {

                graph.addEdge(i, j);
            }
        }
    }

    return graph;
}

}