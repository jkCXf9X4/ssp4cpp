#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"
#include "common_time.hpp"

#include "common_thread_pool.hpp"

#include "invocable.hpp"
#include "analysis_graph_builder.hpp"
#include "graph_builder.hpp"

#include "fmu_handler.hpp"
#include "data_recorder.hpp"

#include "SSP_Ext.hpp"
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
    /**
     * @brief Main class for running a simulation.
     *
     * This class orchestrates the entire simulation process, from loading the SSP
     * file to initializing the FMUs, building the simulation graph, and running
     * the simulation.
     */
    class Simulation
    {
    public:
        common::Logger log = common::Logger("Simulation", common::LogLevel::info);

        Ssp *ssp;

        std::unique_ptr<handler::FmuHandler> fmu_handler;
        std::unique_ptr<utils::DataRecorder> recorder;
        std::unique_ptr<graph::Graph> sim_graph;

        std::string result_file = "results/result.csv";

        /**
         * @brief Constructs a new Simulation object.
         *
         * @param ssp A pointer to the SSP object to be simulated.
         */
        Simulation(Ssp *ssp)
        {
            this->ssp = ssp;

            log.info("[{}] Creating simulation", __func__);
            fmu_handler = std::make_unique<handler::FmuHandler>(this->ssp);
            recorder = std::make_unique<utils::DataRecorder>(result_file);
        }

        /**
         * @brief Initializes the simulation.
         *
         */
        void init()
        {
            log.info("[{}] Initializing simulation", __func__);

            log.info("[{}] - Initializing fmus", __func__);
            fmu_handler->init();

            log.info("[{}] - Creating analysis graph", __func__);
            auto analysis_graph = analysis::graph::AnalysisGraphBuilder(ssp, fmu_handler.get()).build();
            log.debug(" -- {}", analysis_graph->to_string());

            log.info("[{}] - Creating simulation graph", __func__);
            sim_graph = graph::GraphBuilder(analysis_graph.get(), recorder.get()).build();
            log.debug(" -- {}", sim_graph->to_string());

            log.info("[{}] - Init simulation graph", __func__);
            sim_graph->init();

            log.info("[{}] - Initializing recorder", __func__);
            recorder->init();
        }

        /**
         * @brief Runs the simulation.
         *
         * This method runs the simulation from the configured start time to the
         * end time, with the specified timestep. The simulation results are
         * written to the configured output file.
         */
        void simulate()
        {
            recorder->start_recording();
            log.info("[{}] Starting simulation", __func__);

            uint64_t start_time = utils::Config::get<float>("simulation.start_time") * common::time::nanoseconds_per_second;
            uint64_t end_time = utils::Config::get<float>("simulation.end_time") * common::time::nanoseconds_per_second;
            uint64_t timestep = utils::Config::get<float>("simulation.timestep") * common::time::nanoseconds_per_second;

            uint64_t sim_wall_time = 0;
            {
                auto timer = common::time::ScopeTimer("Simulation", &sim_wall_time);
                sim_graph->invoke(sim::graph::StepData(start_time, end_time, timestep));
            }
            log.info("[{}] Simulation completed", __func__);

            uint64_t total_model_time = 0;
            for (auto &node : sim_graph->nodes)
            {
                auto model_walltime = node->invocable_obj->invocation_walltime_ns;
                log.info("[{}] Model {} walltime: {}", __func__, node->invocable_obj->name, model_walltime);
                total_model_time += model_walltime;
            }
            auto sim_wall_time_s = (double)sim_wall_time / common::time::nanoseconds_per_second;
            auto total_model_time_s = (double)total_model_time / common::time::nanoseconds_per_second;
            log.info("[{}] Total walltime: {} Model walltime: {}", __func__, sim_wall_time_s , total_model_time_s);
        }
    };

}