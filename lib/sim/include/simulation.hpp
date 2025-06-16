#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "common_thread_pool.hpp"

#include "graph_builder.hpp"

#include "data_handler.hpp"
#include "data_recorder.hpp"
#include "fmu_handler.hpp"

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

        unique_ptr<handler::DataHandler> data_handler;
        unique_ptr<handler::FmuHandler> fmu_handler;
        unique_ptr<handler::DataRecorder> recorder;

        ssp4cpp::Ssp *ssp;
        std::map<std::string, ssp4cpp::Fmu *> str_fmu;

        unique_ptr<graph::Graph> graph;

        Simulation()
        {
        }

        Simulation(ssp4cpp::Ssp *ssp, std::map<std::string, ssp4cpp::Fmu *> str_fmu)
        {
            fmu_handler = make_unique<handler::FmuHandler>(str_fmu);
            recorder = make_unique<handler::DataRecorder>("temp/raw_data.txt");
            data_handler = make_unique<handler::DataHandler>(10,
                                                             recorder->get_register_buffer_callback(),
                                                             recorder->get_update_callback());

            this->ssp = ssp;
            this->str_fmu = str_fmu;
        }

        void init()
        {
            graph = graph::GraphBuilder()
                        .set_ssp(ssp)
                        .set_fmu_handler(fmu_handler.get())
                        .set_data_handler(data_handler.get())
                        .build();

            graph->print_analysis();

            fmu_handler->init();

            // make analysis
            // - analyze model feedthrough

            // create sim graph
            // - add existing models
            // - add existing connections

            // simplify graph if possible
        }

        // need to think hard aout the time...
        void invoke(graph::ModelNode *node, uint64_t time)
        {
            auto new_time  = node->invoke(time);
            for (auto c_ : node->children)
            {
                auto c = (graph::ModelNode *)c_;
                invoke(c, new_time);
            }
        }

        void execute()
        {

            log.info("[{}] Starting simulation...", __func__);
            ThreadPool pool(5);

            uint64_t time = 0;
            uint64_t end_time = 3 * time::nanoseconds_per_second;
            // uint64_t timestep = 100 * time::nanoseconds_per_millisecond;
            uint64_t timestep = 0.4 * time::nanoseconds_per_second;

            auto start_nodes = graph->get_start_nodes();
            assert(start_nodes.size() == 1);
            auto start_node = start_nodes[0];

            log.info("[{}] Start node: {}", __func__, start_node->to_string());
            // simulation time loop: invoke graph each timestep
            while (time < end_time)
            {
                time += timestep; 

                log.info("[{}] NEW TIME {}", __func__, time);
                invoke(start_node, time);
            }

            recorder->update(); // flush the last updates to file

            log.info("[{}] Simulation completed", __func__);
        }
    };

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

}