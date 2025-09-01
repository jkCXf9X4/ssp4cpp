

#pragma once

#include "common_log.hpp"

#include "invocable.hpp"

#include "model.hpp"
#include "config.hpp"

#include <assert.h>
#include <execution>

namespace ssp4cpp::sim::graph
{


    class ExecutionBase : public Invocable
    {
    public:
        std::vector<Model *> models;

        ExecutionBase(std::vector<Model *> models) : models(std::move(models)) {}
    };

    class Seidel final : public ExecutionBase
    {
    public:
        Model *start_node;
        common::Logger log = common::Logger("Seidel", common::LogLevel::debug);

        Seidel(std::vector<Model *> models) : ExecutionBase(std::move(models))
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

        // need to think hard about the time...
        void invoke_model(Model *model, uint64_t start_time, uint64_t end_time, uint64_t timestep)
        {
            model->invoke(start_time, end_time, timestep, end_time);
            for (auto c_ : model->children)
            {
                auto c = (Model *)c_;
                invoke_model(c, start_time, end_time, timestep);
            }
        }

        uint64_t invoke(uint64_t start_time, uint64_t end_time, uint64_t timestep) override final
        {
            log.ext_trace("[{}] start_time: {} timestep: {} end_time: {}",
                     __func__, start_time, timestep, end_time);

            invoke_model(start_node, start_time, end_time, timestep);
            return end_time;
        }
    };

    class Jacobi final : public ExecutionBase
    {
    public:
        common::Logger log = common::Logger("Jacobi", common::LogLevel::debug);

        bool parallelize;

        Jacobi(std::vector<Model *> models) : ExecutionBase(std::move(models))
        {
            parallelize = utils::Config::get<bool>("simulation.jacobi.parallel");
            log.info("[{}] Parallel: {}", __func__, parallelize);
        }

        friend std::ostream &operator<<(std::ostream &os, const Jacobi &obj)
        {
            os << "Jacobi:\n{}" << std::endl;
            return os;
        }

        uint64_t invoke(uint64_t start_time, uint64_t end_time, uint64_t timestep) override final
        {
            log.ext_trace("[{}] start_time: {} timestep: {} end_time: {}",
                     __func__, start_time, timestep, end_time);

            // If models execute in less than 10-15 microseconds then use sequence
            if (parallelize)
            {
                std::for_each(std::execution::par, models.begin(), models.end(),
                              [&](auto &model)
                              {
                                  model->invoke(start_time, end_time, timestep, start_time);
                              });
            }
            else
            {
                for (auto &model : this->models)
                {
                    model->invoke(start_time, end_time, timestep, start_time);
                }
            }

            return end_time;
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