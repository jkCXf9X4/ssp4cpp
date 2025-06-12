#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "tarjan.hpp"

#include "SSP1_SystemStructureDescription.hpp"

#include "fmu.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{
    class NodeBase : public ssp4cpp::common::graph::Node
    {

    public:
        uint64_t delay = 0;

        common::Logger log = common::Logger("NodeBase", common::LogLevel::ext_trace);

        NodeBase() : Node() {}

        NodeBase(const std::string &name) : ssp4cpp::common::graph::Node(name) {}
    };
}