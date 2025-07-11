#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "fmu_handler.hpp"

#include "analysis_graph.hpp"

#include "sim_model.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::graph
{
    using namespace std;

#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "tarjan.hpp"

#include "node_connection.hpp"
#include "node_model.hpp"
#include "node_connector.hpp"

#include <string>
#include <vector>

    namespace ssp4cpp::sim::graph
    {

        class Graph
        {
        public:
            common::Logger log = common::Logger("Graph", common::LogLevel::debug);

            map<string, unique_ptr<SimModelNode>> models;

            vector<SimModelNode *> nodes;

            Graph() = default;

            Graph(map<string, unique_ptr<SimModelNode>> models_)
                : models(std::move(models_))

            {
                auto m = map_ns::map_unique_to_ref(models);
                nodes = common::map_ns::map_to_value_vector_copy(m);
            }

            vector<SimModelNode *> get_start_nodes()
            {
                auto start_nodes = common::graph::Node::get_ancestors(nodes);
                return start_nodes;
            }
        };

        // // This class can be optimized allot
        // class Connectors
        // {
        // public:

        //     utils::DataStorage input_data(1);
        //     utils::DataStorage output_data(15);

        //     Connectors() {}

        //     void allocate()
        //     {
        //         for (auto [_, con]: input_connectors)
        //         {
        //             input_data.add(*con);
        //         }
        //         for (auto [_, con]: output_connectors)
        //         {
        //             output_data.add(*con);
        //         }
        //         input_data.allocate();
        //         output_data.allocate();
        //     }

        //     void write_to_model(uint64_t time)
        //     {
        //         int index = 0;
        //         for (auto &[_, c] : input_connectors)
        //         {
        //             void *data = c->data_handler->getData(time, c->data_reference);

        //             utils::write_to_model_(c->type, *c->fmu->model, c->value_reference, data);
        //             // storage for export
        //             memcpy(input_data.locations[index], data, input_data.sizes[index]);
        //             index += 1;
        //         }
        //     }

        //     void read_from_model(uint64_t time)
        //     {
        //         int pos = 0;
        //         for (auto &[_, c] : output_connectors)
        //         {
        //             auto d = output_data.locations[pos];
        //             utils::read_from_model_(c->type, *c->fmu->model, c->value_reference, d);

        //             c->data_handler->setData(time, c->data_reference, d);
        //             pos += 1;
        //         }
        //     }

        // };
        using AnalysisGraph = analysis::graph::AnalysisGraph;

        class SimGraphBuilder
        {
        public:
            static inline auto log = common::Logger("sim::graph::GraphBuilder", common::LogLevel::info);

            handler::FmuHandler *fmu_handler;
            AnalysisGraph *analysis_graph;

            SimGraphBuilder(handler::FmuHandler *fmu_handler, AnalysisGraph *ag)
            {
                this->fmu_handler = fmu_handler;
                this->analysis_graph = ag;
            }

            unique_ptr<Graph> build()
            {
                log.ext_trace("[{}] init", __func__);

                              map<string, unique_ptr<SimModelNode>> models;
                for (auto &[ssp_resource_name, model] : analysis_graph->models)
                {
                    auto fmu = (fmu_handler->fmus[ssp_resource_name]).get();

                    auto m = make_unique<SimModelNode>(ssp_resource_name, fmu);
                    log.trace("[{}] New Model: {}", __func__, m->name);
                    models[m->name] = std::move(m);
                }

                models[source]->add_child(models[target].get());


                log.ext_trace("[{}] exit", __func__);
                return make_unique<Graph>(std::move(models));
            }
        };

    }
