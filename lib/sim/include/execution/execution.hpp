#pragma once

#include "common_log.hpp"

#include "invocable.hpp"

#include "config.hpp"

#include <assert.h>
#include <execution>

namespace ssp4cpp::sim::graph
{

    class ExecutionBase : public Invocable
    {
    public:
        std::vector<InvocableNode *> models;

        ExecutionBase(std::vector<InvocableNode *> models) : models(std::move(models)) {}
    };

    class Seidel final : public ExecutionBase
    {
    public:
        InvocableNode *start_node;
        common::Logger log = common::Logger("Seidel", common::LogLevel::debug);

        Seidel(std::vector<InvocableNode *> models) : ExecutionBase(std::move(models))
        {
            auto start_nodes = common::graph::Node::get_ancestors(this->models);
            assert(start_nodes.size() == 1);
            start_node = start_nodes[0];
        }

        friend std::ostream &operator<<(std::ostream &os, const Seidel &obj)
        {
            os << "Seidel:\n{\nStart nodes:\n"
               << "- Start node: " << obj.start_node << "\n}" << std::endl;

            return os;
        }

        void init() override
        {
        }

        // need to think hard about the time...
        void invoke_model(InvocableNode *model, uint64_t start_time, uint64_t end_time, uint64_t timestep)
        {
            auto step = StepData(start_time, end_time, timestep, end_time);
            model->invoke(step);
            for (auto c_ : model->children)
            {
                auto c = (InvocableNode *)c_;
                invoke_model(c, start_time, end_time, timestep);
            }
        }

        uint64_t invoke(StepData step_data) override final
        {
            log.ext_trace("[{}] stepdata: {}", __func__, step_data.to_string());

            invoke_model(start_node, step_data.start_time, step_data.end_time, step_data.timestep);
            return step_data.end_time;
        }
    };

    class Jacobi final : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("Jacobi", common::LogLevel::debug);

        bool parallelize;

        Jacobi(std::vector<InvocableNode *> models) : ExecutionBase(std::move(models))
        {
            parallelize = utils::Config::get<bool>("simulation.jacobi.parallel");
            log.info("[{}] Parallel: {}", __func__, parallelize);
        }

        friend std::ostream &operator<<(std::ostream &os, const Jacobi &obj)
        {
            os << "Jacobi:\n{}" << std::endl;
            return os;
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
                std::for_each(std::execution::par, models.begin(), models.end(),
                              [&](auto &model)
                              {
                                  model->invoke(step);
                              });
            }
            else
            {
                for (auto &model : this->models)
                {
                    model->invoke(step);
                }
            }

            return step_data.end_time;
        }
    };
}

// /**
//  * Traverse the connection graph and invoke nodes when all parents have been invoked for this timestep.
//  */
// void invoke_graph(uint64_t timestep)
// {
// ThreadPool pool(5);
//     // track which nodes have been invoked
//     std::unordered_set<SimNode*> invoked;
//     // start from ancestor nodes (no parents)
//     auto ready = graph::Node::get_ancestors(connection_graph);

//     while (!ready.empty()) {
//         std::vector<SimNode*> next;
//         for (auto node : ready) {
//             node->invoke(timestep);

//             invoked.insert(node);
//             // enqueue children whose all parents are invoked
//             for (auto *child : node->children) {
//                 if (invoked.count(child)) continue;
//                 bool all_parents_invoked = true;
//                 for (auto *p : child->parents) {
//                     if (!invoked.count(p)) {
//                         all_parents_invoked = false;
//                         break;
//                     }
//                 }
//                 if (all_parents_invoked) {
//                     next.push_back(child);
//                 }
//             }
//         }
//         ready.swap(next);
//     }
// }