#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"
#include "tarjan.hpp"

#include "analysis_graph_builder.hpp"
#include "sim_graph_builder.hpp"

#include "ssp_ext.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim
{
    using namespace std;

    class FmuHandler
    {
    public:
        common::Logger log = common::Logger("sim::FmuHandler", common::LogLevel::ext_trace);

        struct fmu_info
        {
            ssp4cpp::Fmu *fmu;
            unique_ptr<fmi4cpp::fmi2::cs_fmu> cs_fmu;
            unique_ptr<fmi4cpp::fmi2::cs_slave> model;
            std::shared_ptr<const fmi4cpp::fmi2::cs_model_description> model_description;
        };

        map<string, fmu_info> fmus;

        FmuHandler(std::map<std::string, ssp4cpp::Fmu *> &str_fmu)
        {
            for (auto &[name, fmu] : str_fmu)
            {
                fmu_info f;
                f.fmu = fmu;
                auto fmu_t = fmi4cpp::fmi2::fmu(fmu->original_file);
                f.cs_fmu = fmu_t.as_cs_fmu();
                f.model_description = f.cs_fmu->get_model_description();

                fmus[name] = std::move(f);
            }
        }

        void init()
        {
            log.trace("[{}] Model init ", __func__);
            for (auto &[_, fmu] : this->fmus)
            {
                fmu.model = fmu.cs_fmu->new_instance();

                fmu.model->setup_experiment();
                fmu.model->enter_initialization_mode();
                fmu.model->exit_initialization_mode();
                // Set up data managers for different types

                // apply parameter sets

                // set start values?
            }
        }
    };

    class VariableHandler
    {
        common::Logger log = common::Logger("sim::VariableHandler", common::LogLevel::ext_trace);

        vector<VariableBase> variables;

        // using Job = std::function<void()>;
        // std::vector<Job> items;

        // A<int>         i{5};
        // A<std::string> s{"hello"};

        // items.emplace_back([i]{ i.print(); }); // copies i into lambda
        // items.emplace_back([s]{ s.print(); });

        // for (auto& job : items) job();         // just run the stored callable
    };

    class Simulation
    {
    public:
        common::Logger log = common::Logger("sim::Simulation", common::LogLevel::ext_trace);

        analysis_graph::AnalysisGraph analysis_graph;
        unique_ptr<sim_graph::SimGraph> graph;

        sim::data::DataManager data;
        sim::FmuHandler fmus;
        sim::VariableHandler variable_handler;

        Simulation() {}

        Simulation(ssp4cpp::Ssp &ssp, std::map<std::string, ssp4cpp::Fmu *> &str_fmu)
            : analysis_graph(analysis_graph::create_analysis_graph(ssp)),
              fmus(str_fmu),
              data(10)
        {

            // make analysis
            // - analyze model feedthrough

            // create sim graph
            // - add existing models
            // - add existing connections

            graph = sim_graph::SimGraphBuilder().create_graph(analysis_graph);

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