#pragma once

#include "network/transmitter.hpp"

namespace rf {

class DistanceCalculator {
public:
    static double calculate(
        const Transmitter& a,
        const Transmitter& b
    );
};

}