#pragma once

#include "network/network.hpp"
#include "physics/interference_model.hpp"
#include "graph/interference_graph.hpp"

namespace rf {

class GraphBuilder {
public:
    static InterferenceGraph build(
        const Network& network,
        const InterferenceModel& model
    );
};

}