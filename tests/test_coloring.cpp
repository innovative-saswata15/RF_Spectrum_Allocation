// Automatic tests for the colouring module. Run: make test
#include "coloring/coloring_metrics.hpp"
#include "coloring/greedy_coloring.hpp"
#include "coloring/vertex_order.hpp"
#include "network/network_generator.hpp"
#include "physics/interference_model.hpp"
#include "graph/graph_builder.hpp"
#include "test_graphs.hpp"

#include <iostream>
#include <string>
#include <utility>

using namespace rf;
using namespace rf::test;

static int passed = 0, failed = 0;

static void check(bool ok, const std::string& name) {
    std::cout << (ok ? "  PASS  " : "  FAIL  ") << name << '\n';
    (ok ? passed : failed)++;
}

static void expectGreedy(const std::string& name,
                         const InterferenceGraph& g,
                         const std::vector<VertexId>& order,
                         std::size_t expectedColors) {
    ColorAssignment colors = GreedyColoring::color(g, order);
    std::size_t used = ColoringMetrics::colorsUsed(colors);
    check(ColoringMetrics::allColored(colors), name + ": every vertex coloured");
    check(ColoringMetrics::conflicts(g, colors) == 0, name + ": no conflicts");
    check(used == expectedColors,
          name + ": " + std::to_string(expectedColors) +
          " colours (got " + std::to_string(used) + ")");
}

int main() {
    std::cout << "== Known graphs ==\n";
    expectGreedy("Empty n=5",   makeEmpty(5),    VertexOrder::natural(5), 1);
    expectGreedy("K5",          makeComplete(5), VertexOrder::natural(5), 5);
    expectGreedy("Path n=7",    makePath(7),     VertexOrder::natural(7), 2);
    expectGreedy("Cycle C6",    makeCycle(6),    VertexOrder::natural(6), 2);
    expectGreedy("Cycle C5",    makeCycle(5),    VertexOrder::natural(5), 3);

    std::cout << "\n== Order matters ==\n";
    InterferenceGraph tower = makeTowerExample();
    expectGreedy("Tower A..F",        tower, VertexOrder::natural(6), 4);
    expectGreedy("Tower B,D,E,C,A,F", tower, {1, 3, 4, 2, 0, 5}, 3);
    for (std::size_t k : {3, 4, 10, 50}) {
        InterferenceGraph crown = makeCrown(k);
        std::string tag = "Crown k=" + std::to_string(k);
        expectGreedy(tag + " bad order",  crown, crownBadOrder(k), k);
        expectGreedy(tag + " rows order", crown, VertexOrder::natural(2 * k), 2);
    }

    std::cout << "\n== Real networks from Member 1's generator ==\n";
    for (std::uint64_t seed = 1; seed <= 3; ++seed) {
        NetworkGenerationConfig config{500, 0.0, 1000.0, 0.0, 1000.0, seed};
        Network network = NetworkGenerator::generate(config);
        InterferenceGraph g = GraphBuilder::build(network, InterferenceModel(80.0));
        std::size_t bound = ColoringMetrics::maxDegree(g) + 1;

        std::vector<std::pair<std::string, std::vector<VertexId>>> orders = {
            {"natural",      VertexOrder::natural(g.vertexCount())},
            {"welsh-powell", VertexOrder::largestDegreeFirst(g)},
            {"random",       VertexOrder::random(g.vertexCount(), seed)},
        };
        for (const auto& [label, order] : orders) {
            ColorAssignment colors = GreedyColoring::color(g, order);
            std::size_t used = ColoringMetrics::colorsUsed(colors);
            std::string tag = "seed " + std::to_string(seed) + " " + label;
            check(ColoringMetrics::conflicts(g, colors) == 0, tag + ": no conflicts");
            check(used <= bound, tag + ": " + std::to_string(used) +
                  " colours <= Delta+1 = " + std::to_string(bound));
        }
    }

    std::cout << "\n== Input validation ==\n";
    bool threw = false;
    try { GreedyColoring::color(makePath(3), {0, 0, 1}); }
    catch (const std::invalid_argument&) { threw = true; }
    check(threw, "Repeated vertex in order is rejected");

    std::cout << '\n' << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
