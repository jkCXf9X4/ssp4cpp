#pragma once

#include "fmu.hpp"
#include "common_node.hpp"

namespace ssp4cpp::cosim::graph
{

    // class FmuNode : public ssp4cpp::common::graph::Node
    // {
    //     Fmu fmu;
    // }

    // class FmuNode : public ssp4cpp::common::graph::Node
    // {
    //     Fmu fmu;
    // }

    class Connector : public ssp4cpp::common::graph::Node
    {
        Fmu fmu;


        Connection() {}

    };

}