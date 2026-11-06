#pragma once

#include "network/transmitter.hpp"

#include <vector>

namespace rf {

class Network {
private:
    std::vector<Transmitter> transmitters_;

public:
    explicit Network(std::vector<Transmitter> transmitters);

    const std::vector<Transmitter>& getTransmitters() const;

    const Transmitter& getTransmitter(VertexId id) const;

    std::size_t size() const;
};

}