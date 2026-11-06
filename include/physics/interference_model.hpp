#pragma once

#include "network/transmitter.hpp"

namespace rf {

class InterferenceModel {
private:
    double interferenceRange_;

public:
    explicit InterferenceModel(double range);

    bool interferes(
        const Transmitter& a,
        const Transmitter& b
    ) const;

    double getRange() const;
};

}