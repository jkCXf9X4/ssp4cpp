#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "common_thread_pool.hpp"

#include "analysis_graph_builder.hpp"
#include "graph_builder.hpp"

#include "fmu_handler.hpp"
#include "data_recorder.hpp"

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
        std::unique_ptr<utils::DataRecorder> recorder;
        
        std::unique_ptr<graph::Graph> sim_graph;

        Ssp *ssp;
        std::map<std::string, Fmu *> fmus;

        std::string result_file = "temp/output.csv";


        Simulation(Ssp *ssp, std::map<std::string, Fmu *> fmus)
        {
            fmu_handler = make_unique<handler::FmuHandler>(fmus);
            recorder = make_unique<utils::DataRecorder>(result_file);

            this->ssp = ssp;
            this->fmus = fmus;
        }

        void init()
        {
            log.info("[{}] Initializing simulation...", __func__);
            auto analysis_graph = analysis::graph::AnalysisGraphBuilder(ssp, fmu_handler.get()).build();
            log.info("{}", analysis_graph->to_string());
            log.info("[{}] Analysis graph completed", __func__);
            
            sim_graph = graph::GraphBuilder(analysis_graph.get(), recorder.get()).build();
            log.info("{}", sim_graph->to_string());
            log.info("[{}] Simulation graph completed", __func__);
            
            
            log.info("[{}] Initializing fmu handler", __func__);
            fmu_handler->init();
            log.info("[{}] Initializing recorder", __func__);
            recorder->init();
        }

        void simulate()
        {

            log.info("[{}] Starting simulation...", __func__);
            recorder->start_recording();


            uint64_t time = 0.1;
            uint64_t end_time = 2 * time::nanoseconds_per_second;
            uint64_t timestep = 0.1 * time::nanoseconds_per_second;

            auto start = std::chrono::high_resolution_clock::now();

            while (time < end_time)
            {
                time += timestep;

                log.ext_trace("[{}] NEW TIME {}", __func__, time);
                sim_graph->invoke(time);
            }

            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::microseconds>(stop - start);
            log.info("[{}] Simulation completed.\n Duration: {}ns", __func__, duration.count());
            
            recorder->stop_recording();
            
            log.info("[{}] The End", __func__);
        }
    };


}