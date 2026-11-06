#include "network/transmitter.hpp"

namespace rf {

Transmitter::Transmitter(VertexId id, double x, double y)
    : id_(id), x_(x), y_(y) {}

VertexId Transmitter::getId() const {
    return id_;
}

double Transmitter::getX() const {
    return x_;
}

double Transmitter::getY() const {
    return y_;
}

}