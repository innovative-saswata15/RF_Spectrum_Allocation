#pragma once

#include <cstddef>

namespace rf {

using VertexId = std::size_t;

class Transmitter {
private:
    VertexId id_;
    double x_;
    double y_;

public:
    Transmitter(VertexId id, double x, double y);

    VertexId getId() const;
    double getX() const;
    double getY() const;
};

}