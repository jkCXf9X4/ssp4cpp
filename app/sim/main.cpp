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

#include "system_builder.hpp"

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

namespace ssp4cpp::sim
{

    class Simulator
    {
    public:
        common::Logger log = Logger("Simulator", LogLevel::debug);

        unique_ptr<Ssp> ssp;
        std::map<std::string, std::unique_ptr<ssp4cpp::Fmu>> fmus;
        std::map<std::string, ssp4cpp::Fmu *> fmus_ref;

        common::json::Json model_props;

        // system_graph: Simple graph only showing the connections between fmu's
        sim_gr
            ::SystemGraph system_graph;

        Simulator(const string &ssp_path,
                  const string &props_path)
        {
            ssp = make_unique<ssp4cpp::Ssp>(ssp_path);
            log.debug("[{}] SSP: {}", __func__, ssp->to_string());

            fmus = ssp4cpp::ssp::ext::create_fmu_map(this->ssp);
            for (auto &[fmu_name, fmu] : fmus)
                log.debug("[{}] FMU: {} - ", __func__, fmu_name, fmu->to_string());

            fmus_ref = map_ns::map_unique_to_ref(fmus);

            model_props = json::parse_json_file(props_path);
            log.debug("[{}] Extra properties:\n{}\n", __func__, json::to_string(model_props));

            system_graph = sim::graph::SystemGraph(ssp.get());
        }

        ~Simulator()
        {
            // unique_ptr will automatically clean up FMUs and SSP
            // when this is destroyed the application will end, no need to free memory resources
        }

        void invoke(SimNode *node, uint64_t timestep)
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
            uint64_t timestep = 100 * time::nanosecond_per_millisecond;

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

int main()
{
    auto log = Logger("main", LogLevel::debug);
    log.info("[{}] enter", __func__);

    // auto sim = Simulator("./resources/algebraic_loop_4.ssp", "./resources/model_props.json");
    auto sim = Simulator("./resources/delay_sys.ssp", "./resources/model_props.json");
    sim.execute();

    log.info("[{}] exit", __func__);
    return 0;
}
