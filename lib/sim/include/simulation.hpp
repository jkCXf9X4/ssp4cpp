#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "graph_builder.hpp"

#include "data_handler.hpp"
#include "fmu_handler.hpp"
#include "variable_handler.hpp"

#include "ssp_ext.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim
{
    using namespace std;

    class Simulation
    {
    public:
        common::Logger log = common::Logger("sim::Simulation", common::LogLevel::ext_trace);

        unique_ptr<graph::Graph> graph;

        unique_ptr<handler::DataHandler> data_handler;
        unique_ptr<handler::FmuHandler> fmu_handler;
        unique_ptr<handler::VariableHandler> variable_handler;

        Simulation() {}

        Simulation(ssp4cpp::Ssp* ssp, std::map<std::string, ssp4cpp::Fmu *> &str_fmu)
        {
            data_handler = make_unique<handler::DataHandler>(10);
            fmu_handler = make_unique<handler::FmuHandler>(str_fmu);
            variable_handler = make_unique<handler::VariableHandler>();

            graph = GraphBuilder().set_ssp(ssp) .build()
            
            // make analysis
            // - analyze model feedthrough

            // create sim graph
            // - add existing models
            // - add existing connections

            // simplify graph if possible
        }

        void invoke(sim_graph::Model *node, uint64_t timestep)
        {
            for (auto c_ : node->children)
            {
                auto c = (SimNode *)c_;
                c->invoke(timestep);
                invoke(c, timestep);
            }
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

        void execute()
        {

            log.info("[{}] Starting simulation...", __func__);
            ThreadPool pool(5);

            uint64_t time = 0;
            uint64_t end_time = 10 * time::nanoseconds_per_second;
            uint64_t timestep = 100 * time::nanoseconds_per_millisecond;

            auto start_nodes = system_graph.get_start_nodes();
            assert(start_nodes.size() == 1);
            auto start_node = start_nodes[0];

            for (auto node : *start_node)
            {
                auto n = (SimNode *)node;
                n->init();
            }

            // simulation time loop: invoke graph each timestep
            while (time < end_time)
            {
                invoke(start_node, timestep);
                time += timestep;
            }

            log.info("[{}] Simulation completed", __func__);
        }
    };

}