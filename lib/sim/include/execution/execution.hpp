#pragma once

#include "common_log.hpp"

#include "invocable.hpp"
#include "async_node.hpp"

#include "config.hpp"

#include <assert.h>
#include <execution>

namespace ssp4cpp::sim::graph
{

    class ExecutionBase : public Invocable
    {
    public:
        std::vector<AsyncNode *> nodes;
        std::vector<std::size_t> nr_parents;
        std::vector<std::size_t> nr_parents_counter;

        bool parallelize;
        std::unique_ptr<SharedState> shared_state;

        ExecutionBase(std::vector<AsyncNode *> nodes) : nodes(std::move(nodes))
        {
            shared_state = std::make_unique<SharedState>();

            for (int i = 0; i < nodes.size(); i++)
            {
                nodes[i]->set_shared_state(i, shared_state.get());
            }

            for (auto &m : nodes)
            {
                nr_parents.push_back(m->parents.size());
                nr_parents_counter.push_back(m->parents.size());
            }
        }
    };

    class Seidel final : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("Seidel", common::LogLevel::debug);

        // std::vector<ssp4cpp::sim::graph::AsyncNode *> start_nodes;

        Seidel(std::vector<AsyncNode *> nodes) : ExecutionBase(std::move(nodes))
        {
            parallelize = utils::Config::get<bool>("simulation.seidel.parallel");
            log.info("[{}] Parallel: {}", __func__, parallelize);
        }

        virtual void print(std::ostream &os) const
        {
            os << "Seidel:\n{}" << std::endl;
        }

        void init() override
        {
        }

        /**
         * Traverse the connection graph and invoke nodes when all parents have been invoked for this timestep.
         */
        void invoke_graph(StepData step)
        {
            // track how many are currently running
            int launched = 0;
            int completed = 0;

            // start from ancestor nodes (no parents)
            for (int i = 0; i < nodes.size(); i++)
            {
                // reset all counters, no allocation
                this->nr_parents_counter[i] = this->nr_parents[i];
                auto node = nodes[i];

                // starting all models without parents
                if (this->nr_parents_counter[i] == 0)
                {
                    log.info("[{}] Invoking: {}", __func__, node->name);
                    node->async_invoke(step);
                    launched += 1;
                }
            }

            while (launched == completed)
            {
                shared_state->sem.acquire();
                completed += 1;

                DoneMsg msg;
                {
                    std::lock_guard<std::mutex> lock(shared_state->mtx);
                    msg = std::move(shared_state->inbox.front());
                    shared_state->inbox.pop();
                }
                auto finished_node = nodes[msg.worker_id];

                // enqueue children whose all parents are invoked
                for (auto n : finished_node->children)
                {
                    AsyncNode *node = (AsyncNode *)n;
                    this->nr_parents_counter[node->worker_id] -= 1;
                    if (this->nr_parents_counter[node->worker_id] == 0)
                    {
                        log.info("[{}] Invoking: {}", __func__, node->name);
                        node->async_invoke(step);
                        launched += 1;
                    }
                }
            }
        }

        uint64_t invoke(StepData step_data) override final
        {
            log.ext_trace("[{}] stepdata: {}", __func__, step_data.to_string());
            step_data.valid_input_time = step_data.end_time;

            invoke_graph(step_data);
            return step_data.end_time;
        }
    };

    class Jacobi final : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("Jacobi", common::LogLevel::debug);

        bool parallelize;

        Jacobi(std::vector<AsyncNode *> nodes) : ExecutionBase(std::move(nodes))
        {
            parallelize = utils::Config::get<bool>("simulation.jacobi.parallel");
            log.info("[{}] Parallel: {}", __func__, parallelize);
        }

        virtual void print(std::ostream &os) const
        {
            os << "Jacobi:\n{}" << std::endl;
        }

        void init() override
        {
        }

        uint64_t invoke(StepData step_data) override final
        {
            log.ext_trace("[{}] stepdata: {}", __func__, step_data.to_string());

            // If models execute in less than 10-15 microseconds then use sequence
            auto step = StepData(step_data.start_time, step_data.end_time, step_data.timestep, step_data.start_time);
            if (parallelize)
            {
                std::for_each(std::execution::par, nodes.begin(), nodes.end(),
                              [&](auto &model)
                              {
                                  model->invoke(step);
                              });
            }
            else
            {
                for (auto &model : this->nodes)
                {
                    model->invoke(step);
                }
            }

            return step_data.end_time;
        }
    };
}
