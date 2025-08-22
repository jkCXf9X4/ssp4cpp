#pragma once

#include "common_log.hpp"
#include "common_map.hpp"
#include "common_vector.hpp"

#include "model.hpp"

#include <vector>
#include <algorithm>
#include <map>

namespace ssp4cpp::sim::graph
{

    class Graph
    {
    public:
        common::Logger log = common::Logger("Graph", common::LogLevel::debug);

        std::map<string, unique_ptr<Model>> models;

        std::vector<Model *> nodes;
        Model * start_node;

        Graph() = default;

        Graph(std::map<string, unique_ptr<Model>> models_)
            : models(std::move(models_))
        {
            auto m = map_ns::map_unique_to_ref(models);
            nodes = common::map_ns::map_to_value_vector_copy(m);

            auto start_nodes = get_start_nodes();
            assert(start_nodes.size() == 1);
            start_node = start_nodes[0];
        }

        vector<Model *> get_start_nodes() const
        {
            auto start_nodes = common::graph::Node::get_ancestors(nodes);
            return start_nodes;
        }

        friend std::ostream &operator<<(std::ostream &os, const Graph &obj)
        {
            auto strong_system_graph = common::graph::strongly_connected_components(common::graph::Node::cast_to_parent_ptrs(obj.nodes));
            
            os << "Simulation Graph DOT:\n" 
            << common::graph::Node::to_dot(obj.nodes) << std::endl
            << common::graph::ssc_to_string(strong_system_graph) << std::endl;

            os << "Start nodes:" << std::endl;
            for (auto &model : obj.get_start_nodes())
            {
                os << "Model: " << model->name << std::endl;
            }

            os << "Storage areas:" << std::endl;
            for (auto &[name, model] : obj.models)
            {
                os << "Model: " << name << std::endl
                << " Input: " << *model->input_area << std:: endl
                << " Output: " << *model->output_area << std::endl;
            }
            return os;
        }

        /** @brief Convert to string for debugging purposes. */
        std::string to_string()
        {
            return common::str::stream_to_str(*this);
        }

                // need to think hard about the time...
        void invoke_model(graph::Model *node, uint64_t time)
        {
            auto new_time = node->invoke(time);
            for (auto c_ : node->children)
            {
                auto c = (graph::Model *)c_;
                invoke_model(c, new_time);
            }
        }

        uint64_t invoke(uint64_t time)
        {
            invoke_model(start_node, time);
            return time;
        }


    // /**
    //  * Traverse the connection graph and invoke nodes when all parents have been invoked for this timestep.
    //  */
    // void invoke_graph(uint64_t timestep)
    // {
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
    };

}