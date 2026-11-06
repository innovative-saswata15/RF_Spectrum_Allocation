#include "physics/interference_model.hpp"
#include "physics/distance_calculator.hpp"

#include <cmath>
#include <stdexcept>

namespace rf {

InterferenceModel::InterferenceModel(double range)
    : interferenceRange_(range) {

    if (!std::isfinite(range) || range < 0.0) {
        throw std::invalid_argument(
            "Interference range must be finite and non-negative"
        );
    }
}

bool InterferenceModel::interferes(
    const Transmitter& a,
    const Transmitter& b
) const {

    if (a.getId() == b.getId()) {
        return false;
    }

    double distance = DistanceCalculator::calculate(a, b);

    return distance <= interferenceRange_;
}

double InterferenceModel::getRange() const {
    return interferenceRange_;
}

}