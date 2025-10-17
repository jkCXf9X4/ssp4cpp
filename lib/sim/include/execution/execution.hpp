#pragma once

#include "common_log.hpp"

#include "invocable.hpp"

namespace ssp4cpp::sim::graph
{

    class ExecutionBase : public Invocable
    {
    public:
        common::Logger log = common::Logger("ssp4sim.execution.ExecutionBase", common::LogLevel::info);
        std::vector<Invocable *> nodes;


        ExecutionBase(std::vector<Invocable *> nodes) : nodes(std::move(nodes))
        {
            log.trace("[{}] Setting up shared state", __func__);

            for (int i = 0; i < this->nodes.size(); i++)
            {
                this->nodes[i]->id = i;
            }
        }
    };
}
