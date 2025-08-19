#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "common_thread_pool.hpp"

#include "graph_builder.hpp"
#include "sim_graph_builder.hpp"

#include "fmu_handler.hpp"

// #include "csv_converter.hpp"

#include "ssp_ext.hpp"
#include "ssp.hpp"
#include "fmu.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <chrono>

namespace ssp4cpp::sim
{
    using namespace std;

    class Simulation
    {
    public:
        common::Logger log = common::Logger("sim::Simulation", common::LogLevel::debug);

        std::unique_ptr<handler::FmuHandler> fmu_handler;
        // std::unique_ptr<utils::DataRecorder> recorder;
        
        std::unique_ptr<graph::Graph> sim_graph;

        Ssp *ssp;
        std::map<std::string, Fmu *> fmus;

        std::string temp_file = "temp/raw_data.txt";


        Simulation(Ssp *ssp, std::map<std::string, Fmu *> fmus)
        {
            fmu_handler = make_unique<handler::FmuHandler>(fmus);
            // recorder = make_unique<utils::DataRecorder>(temp_file);

            this->ssp = ssp;
            this->fmus = fmus;
        }

        void init()
        {
            auto analysis_graph = analysis::graph::GraphBuilder(ssp, fmu_handler.get()).build();
            analysis_graph->print_analysis();

            sim_graph = graph::SimGraphBuilder(analysis_graph.get()).build();

            sim_graph->print_info();

            fmu_handler->init();
        }

        // need to think hard about the time...
        void invoke(graph::SimModelNode *node, uint64_t time)
        {
            auto new_time = node->invoke(time);
            for (auto c_ : node->children)
            {
                auto c = (graph::SimModelNode *)c_;
                invoke(c, new_time);
            }
        }

        void execute()
        {

            log.info("[{}] Starting simulation...", __func__);
            ThreadPool pool(5);

            uint64_t time = 0;
            uint64_t end_time = 2 * time::nanoseconds_per_second;
            uint64_t timestep = 0.1 * time::nanoseconds_per_second;

            auto start_nodes = sim_graph->get_start_nodes();
            assert(start_nodes.size() == 1);
            auto start_node = start_nodes[0];

            auto start = std::chrono::high_resolution_clock::now();
            // simulation time loop: invoke graph each timestep
            while (time < end_time)
            {
                time += timestep;

                log.ext_trace("[{}] NEW TIME {}", __func__, time);
                invoke(start_node, time);
            }
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);
            log.info("[{}] Simulation completed, {}", __func__, duration.count());
            
            // sleep(1);        // give the buffer time to flush to file
            
            log.info("[{}] Saving output", __func__);
            // convert_to_csv(temp_file, "temp/output.csv");
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