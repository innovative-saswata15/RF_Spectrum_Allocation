#include "network/network_generator.hpp"
#include "physics/interference_model.hpp"
#include "graph/graph_builder.hpp"

#include <iostream>

int main() {

    // 1. Configure network generation
    rf::NetworkGenerationConfig config{
        10,       // Number of transmitters
        0.0, 100.0,  // X boundaries
        0.0, 100.0,  // Y boundaries
        42        // Random seed
    };

    // 2. Generate network
    rf::Network network =
        rf::NetworkGenerator::generate(config);

    // 3. Define interference model
    rf::InterferenceModel model(25.0);

    // 4. Construct interference graph
    rf::InterferenceGraph graph =
        rf::GraphBuilder::build(network, model);

    // 5. Display network information
    std::cout << "Number of transmitters: "
              << network.size() << '\n';

    std::cout << "Number of vertices: "
              << graph.vertexCount() << '\n';

    std::cout << "Number of edges: "
              << graph.edgeCount() << '\n';

    // 6. Display adjacency list
    std::cout << "\nInterference Graph:\n";

    for (rf::VertexId i = 0; i < graph.vertexCount(); ++i) {

        std::cout << "T" << i << " -> ";

        for (rf::VertexId neighbor : graph.getNeighbors(i)) {
            std::cout << "T" << neighbor << " ";
        }

        std::cout << '\n';
    }

    std::cout << "\nGraph valid: "
              << (graph.isValid() ? "Yes" : "No")
              << '\n';

    return 0;
}