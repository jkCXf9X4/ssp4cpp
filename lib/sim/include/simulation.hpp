#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"
#include "common_time.hpp"

#include "common_thread_pool.hpp"

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
    using namespace std;

    class Simulation
    {
    public:
        common::Logger log = common::Logger("Simulation", common::LogLevel::info);

        Ssp *ssp;

        std::unique_ptr<handler::FmuHandler> fmu_handler;
        std::unique_ptr<utils::DataRecorder> recorder;
        std::unique_ptr<graph::Graph> sim_graph;

        std::string result_file = "temp/output.csv";

        Simulation(Ssp *ssp)
        {
            this->ssp = ssp;

            log.info("[{}] Creating simulation", __func__);
            fmu_handler = make_unique<handler::FmuHandler>(this->ssp);
            recorder = make_unique<utils::DataRecorder>(result_file);
        }

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

        void simulate()
        {
            log.info("[{}] Starting simulation", __func__);
            recorder->start_recording();

            uint64_t start_time = utils::Config::get<float>("simulation.start_time") * time::nanoseconds_per_second;
            uint64_t end_time = utils::Config::get<float>("simulation.end_time") * time::nanoseconds_per_second;
            uint64_t timestep = utils::Config::get<float>("simulation.timestep") * time::nanoseconds_per_second;

            {
                auto timer = common::time::ScopeTimer("Simulation");
                sim_graph->invoke(start_time, end_time, timestep);
            }
            recorder->stop_recording();

            log.info("[{}] Simulation completed", __func__);
        }
    };

}