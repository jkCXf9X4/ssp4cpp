#pragma once

#include "common_log.hpp"

#include "common_definitions.hpp"

#include "execution.hpp"

#include "model_async.hpp"
#include "task_thread_pool.hpp"
#include "task_thread_pool2.hpp"

#include "config.hpp"

#include <assert.h>
#include <execution>

namespace ssp4cpp::sim::graph
{
    struct SeidelNode
    {
        int id;
        AsyncNode *node;
        std::size_t nr_parents;
        std::size_t nr_parents_counter;
        SeidelNode() {}
    };

    class SeidelBase : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("SeidelBase", common::LogLevel::info);

        const int nr_of_nodes = 0;
        std::vector<SeidelNode> seidel_nodes;
        std::vector<SeidelNode *> start_nodes;

        SeidelBase(std::vector<AsyncNode *> _nodes_) : ExecutionBase(std::move(_nodes_)), nr_of_nodes(nodes.size()), seidel_nodes(nr_of_nodes)
        {
            log.info("[{}] ", __func__);
            log.trace("[{}] nr_of_nodes {}, seidel_nodes {}", __func__, nr_of_nodes, seidel_nodes.size());

            for (auto &node : this->nodes)
            {
                auto id = node->worker_id;

                auto &n = seidel_nodes[id];
                n.id = id;
                n.node = node;
                n.nr_parents = node->parents.size();
                n.nr_parents_counter = n.nr_parents;

                log.ext_trace("[{}] Assigning SeidelNode {}", __func__, id);
            }

            log.info("[{}] Evaluating start nodes", __func__);
            for (auto &node : this->seidel_nodes)
            {
                if (node.node->nr_parents() == 0)
                {
                    start_nodes.push_back(&node);
                }
            }
        }

        inline void reset_counters()
        {
            for (auto &n : seidel_nodes)
            {
                n.nr_parents_counter = n.nr_parents;
            }
        }
    };

    class SerialSeidel final : public SeidelBase
    {
    public:
        common::Logger log = common::Logger("Seidel", common::LogLevel::info);

        SerialSeidel(std::vector<AsyncNode *> nodes) : SeidelBase(std::move(nodes))
        {
            log.info("[{}] ", __func__);
        }

        virtual void print(std::ostream &os) const
        {
            os << "SerialSeidel:\n{}\n";
        }

        void init() override
        {
        }

        // some idea that this might be more effective than looping over all items
        // Not used at the moment
        inline void invoke_node(SeidelNode &node, StepData step_data)
        {
            node.node->invoke(step_data);
            for (auto c : node.node->children)
            {
                auto &child = seidel_nodes[((AsyncNode *)c)->worker_id];
                child.nr_parents_counter -= 1;
                if (child.nr_parents_counter == 0)
                {
                    invoke_node(child, step_data);
                }
            }
        }

        /**
         * Traverse the connection graph and invoke nodes when all parents have been invoked for this timestep.
         * [hot path]
         */
        uint64_t invoke(StepData step_data, const bool only_feedthrough = false) override final
        {
            IF_LOG({
                log.ext_trace("[{}] step data: {}", __func__, step_data.to_string());
            });

            step_data.valid_input_time = step_data.end_time;

            int completed = 0;
            reset_counters();

            IF_LOG({
                log.trace("[{}] Invoking nodes", __func__);
            });

            while (nr_of_nodes != completed)
            {
                for (auto &node : seidel_nodes)
                {
                    if (node.nr_parents_counter == 0)
                    {

                        IF_LOG({
                            log.trace("[{}] Starting", __func__, node.id);
                        });

                        node.node->invoke(step_data);
                        for (auto c : node.node->children)
                        {
                            auto &child = seidel_nodes[((AsyncNode *)c)->worker_id];
                            child.nr_parents_counter -= 1;
                        }
                    }
                }
            }

            IF_LOG({
                log.trace("[{}] End. completed  {}", __func__, completed);
            });

            return step_data.end_time;
        }
    };

    class ParallelSeidel final : public SeidelBase
    {
    public:
        common::Logger log = common::Logger("Seidel", common::LogLevel::info);

        ParallelSeidel(std::vector<AsyncNode *> nodes) : SeidelBase(std::move(nodes))
        {
            log.info("[{}]", __func__);
        }

        virtual void print(std::ostream &os) const
        {
            os << "ParallelSeidel:\n{}\n";
        }

        void init() override
        {
        }

        /**
         * Traverse the connection graph and invoke nodes when all parents have been invoked for this timestep.
         * [hot path]
         */
        uint64_t invoke(StepData step_data, const bool only_feedthrough = false) override final
        {
            IF_LOG({
                log.ext_trace("[{}] step data: {}", __func__, step_data.to_string());
            });

            step_data.valid_input_time = step_data.end_time;

            reset_counters();

            // track how many are currently running
            int launched = 0;
            int completed = 0;

            IF_LOG({
                log.trace("[{}] Invoking all start nodes", __func__);
            });

            for (auto &sn : start_nodes)
            {
                sn->node->async_invoke(step_data);
                launched += 1;
            }

            while (launched != completed)
            {
                IF_LOG({
                    log.trace("[{}] Waiting for nodes to finish. launched {}, completed  {}", __func__, launched, completed);
                });

                shared_state->sem.acquire();
                completed += 1;

                DoneMsg msg;
                {
                    std::lock_guard<std::mutex> lock(shared_state->mtx);
                    msg = std::move(shared_state->inbox.front());
                    shared_state->inbox.pop();
                }
                auto &finished_node = seidel_nodes[msg.worker_id];

                IF_LOG({
                    log.trace("[{}] Node finished: {}", __func__, finished_node.node->name);
                });

                // enqueue children whose all parents are invoked
                for (auto c : finished_node.node->children)
                {
                    auto &child = seidel_nodes[((AsyncNode *)c)->worker_id];

                    child.nr_parents_counter -= 1;
                    if (child.nr_parents_counter == 0)
                    {
                        IF_LOG({
                            log.debug("[{}] Node ready, invoking: {}", __func__, child.node->name);
                        });

                        child.node->async_invoke(step_data);
                        launched += 1;
                    }
                }
            }
            IF_LOG({
                log.trace("[{}] End. launched {}, completed  {}", __func__, launched, completed);
            });

            return step_data.end_time;
        }
    };
}
