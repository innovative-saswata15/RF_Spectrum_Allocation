#pragma once

#include "network/network.hpp"

#include <cstdint>

namespace rf {

struct NetworkGenerationConfig {
    std::size_t transmitterCount;

    double minX;
    double maxX;

    double minY;
    double maxY;

    std::uint64_t seed;
};

class NetworkGenerator {
public:
    static Network generate(
        const NetworkGenerationConfig& config
    );
};

}