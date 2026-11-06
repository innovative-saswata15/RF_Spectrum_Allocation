#include "network/network.hpp"

#include <stdexcept>
#include <utility>

namespace rf {

Network::Network(std::vector<Transmitter> transmitters)
    : transmitters_(std::move(transmitters)) {

    for (std::size_t i = 0; i < transmitters_.size(); ++i) {
        if (transmitters_[i].getId() != i) {
            throw std::invalid_argument(
                "Transmitter IDs must be continuous from 0"
            );
        }
    }
}

const std::vector<Transmitter>& Network::getTransmitters() const {
    return transmitters_;
}

const Transmitter& Network::getTransmitter(VertexId id) const {
    return transmitters_.at(id);
}

std::size_t Network::size() const {
    return transmitters_.size();
}

}