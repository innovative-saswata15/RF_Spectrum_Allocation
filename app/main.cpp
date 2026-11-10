#include "network/network_generator.hpp"
#include "physics/interference_model.hpp"
#include "graph/graph_builder.hpp"
#include "coloring/greedy_coloring.hpp"
#include "coloring/vertex_order.hpp"
#include "coloring/coloring_metrics.hpp"

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

    // 7. Channel allocation (Member 2)
    rf::ColorAssignment colors = rf::GreedyColoring::color(
        graph, rf::VertexOrder::natural(graph.vertexCount())
    );

    std::cout << "\nGreedy channel allocation:\n";
    for (rf::VertexId i = 0; i < graph.vertexCount(); ++i) {
        std::cout << "T" << i << " -> channel " << colors[i] << '\n';
    }

    std::cout << "Channels used: "
              << rf::ColoringMetrics::colorsUsed(colors)
              << "  (Delta + 1 bound = "
              << rf::ColoringMetrics::maxDegree(graph) + 1 << ")\n";
    std::cout << "Conflicts: "
              << rf::ColoringMetrics::conflicts(graph, colors) << '\n';

    return 0;
}