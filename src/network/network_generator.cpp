#include "network/network_generator.hpp"

#include <random>
#include <stdexcept>
#include <vector>

namespace rf {

Network NetworkGenerator::generate(
    const NetworkGenerationConfig& config
) {
    if (config.minX > config.maxX ||
        config.minY > config.maxY) {
        throw std::invalid_argument("Invalid coordinate boundaries");
    }

    std::mt19937_64 engine(config.seed);

    std::uniform_real_distribution<double> xDistribution(
        config.minX, config.maxX
    );

    std::uniform_real_distribution<double> yDistribution(
        config.minY, config.maxY
    );

    std::vector<Transmitter> transmitters;

    transmitters.reserve(config.transmitterCount);

    for (VertexId i = 0; i < config.transmitterCount; ++i) {

        double x = xDistribution(engine);
        double y = yDistribution(engine);

        transmitters.emplace_back(i, x, y);
    }

    return Network(std::move(transmitters));
}

}