#include "physics/distance_calculator.hpp"

#include <cmath>

namespace rf {

double DistanceCalculator::calculate(
    const Transmitter& a,
    const Transmitter& b
) {
    double dx = a.getX() - b.getX();
    double dy = a.getY() - b.getY();

    return std::hypot(dx, dy);
}

}