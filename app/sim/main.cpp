#include "ssp.hpp"
#include "fmu.hpp"
#include "ssp_ext.hpp"
#include "common_io.hpp"
#include "common_log.hpp"
#include "common_string.hpp"
#include "common_node.hpp"
#include "common_json.hpp"
#include "common_node.hpp"
#include "common_map.hpp"
#include "common_thread_pool.hpp"
#include "common_time.hpp"
#include <unordered_set>


#include "tarjan.hpp"

#include "SSP1_SystemStructureDescription_Ext.hpp"
#include "FMI2_modelDescription_Ext.hpp"

#include "simnode.hpp"
#include "system_graph.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

using namespace std;
using namespace ssp4cpp;
using namespace common::io;
using namespace common;

using SimNode = sim::graph::SimNode;

class Simulator
{
public:
    common::Logger log = Logger("Simulator", LogLevel::debug);

    unique_ptr<Ssp> ssp;
    common::json::Json model_props;

    // system_graph: Simple graph only showing the connections between fmu's
    sim::graph::SystemGraph system_graph;

    Simulator(const string &ssp_path,
              const string &props_path)
    {
        ssp = make_unique<ssp4cpp::Ssp>(ssp_path);
        log.debug("SSP: {}", ssp->to_string());

        model_props = json::parse_json_file(props_path);
        log.debug("Extra properties:\n{}\n", json::to_string(model_props));

        system_graph = sim::graph::SystemGraph(ssp.get());

        // // system graph
        // system_graph = ssp4cpp::sim::graph::create_system_graph(*ssp, fmu_map_ref);
        // connection_graph = ssp4cpp::sim::graph::create_connection_graph(*ssp, fmu_map_ref);
        // auto feedthrough_graph = ssp4cpp::sim::graph::create_feedthrough_graph(*ssp, fmu_map_ref);

        // auto strong_system_graph = graph::strongly_connected_components(SimNode::cast_to_parent_ptrs(system_graph));
        // auto strong_connection_graph = graph::strongly_connected_components(SimNode::cast_to_parent_ptrs(connection_graph));
        // // auto strong_feedthrough_graph = graph::strongly_connected_components(SimNode::cast_to_parent_ptrs(feedthrough_graph));

        // log.info("system_graph DOT \n{}", SimNode::to_dot(system_graph));
        // log.info("connection_graph DOT \n{}", SimNode::to_dot(connection_graph));
        // // log.info("feedthrough_graph DOT \n{}", SimNode::to_dot(feedthrough_graph));

        // log.info("{}", graph::ssc_to_string(strong_system_graph));
        // log.info("{}", graph::ssc_to_string(strong_connection_graph));
        // // log.info("{}", graph::ssc_to_string(strong_feedthrough_graph));

    }

    ~Simulator()
    {
        // unique_ptr will automatically clean up FMUs and SSP
        // when this is destroyed the application will end, no need to free memory resources
    }

    auto invoke(SimNode * node, uint64_t timestep)
    {
        for (auto c_ : node->children)
        {
            auto c = (SimNode*)c_;
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
        uint64_t end_time = 10 * time::nanoseconds_per_seconds;
        uint64_t timestep = 1 * time::milliseconds_per_seconds;

        auto start_nodes = graph::Node::get_ancestors(connection_graph);
        assert(start_nodes.size() == 1);
        auto start_node = start_nodes[0];

        // simulation time loop: invoke graph each timestep
        while (time < end_time)
        {
            invoke(start_node, timestep);
            time += timestep;
        }
        
        log.info("[{}] Simulation completed", __func__);
    }
};

int main()
{
    auto log = Logger("main", LogLevel::debug);
    log.info("[{}] enter", __func__);

    auto sim = Simulator("./resources/algebraic_loop_4.ssp", "./resources/model_props.json");
    sim.execute();
    
    
    log.info("[{}] exit", __func__);
    return 0;
}
