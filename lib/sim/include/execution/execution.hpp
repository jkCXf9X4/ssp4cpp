#pragma once

#include "common_log.hpp"

#include "invocable.hpp"
#include "model_async.hpp"

namespace ssp4cpp::sim::graph
{

    class ExecutionBase : public Invocable
    {
    public:
        common::Logger log = common::Logger("ssp4sim.execution.ExecutionBase", common::LogLevel::info);
        std::vector<AsyncNode *> nodes;

        std::unique_ptr<SharedState> shared_state;

        ExecutionBase(std::vector<AsyncNode *> nodes) : nodes(std::move(nodes))
        {
            log.trace("[{}] Setting up shared state", __func__);
            shared_state = std::make_unique<SharedState>();

            for (int i = 0; i < this->nodes.size(); i++)
            {
                this->nodes[i]->set_shared_state(i, shared_state.get());
            }
        }
    };
}
