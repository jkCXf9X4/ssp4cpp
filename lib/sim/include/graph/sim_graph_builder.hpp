#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"
#include "common_log.hpp"

#include "fmu_handler.hpp"

#include "analysis_graph.hpp"

#include "sim_model.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <string>

#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"
#include "tarjan.hpp"

#include "node_connection.hpp"
#include "node_model.hpp"
#include "node_connector.hpp"

namespace ssp4cpp::sim::graph
{
    using namespace std;

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

        void print_info()
        {
            log.info("simulation DOT: \n{}", common::graph::Node::to_dot(nodes));

            auto strong_system_graph = common::graph::strongly_connected_components(common::graph::Node::cast_to_parent_ptrs(nodes));
            log.info("{}", common::graph::ssc_to_string(strong_system_graph));

            log.info("Start nodes:");
            for (auto &model : get_start_nodes())
            {
                log.info("Model: {}", model->to_string());
            }
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

        AnalysisGraph *analysis_graph;

        SimGraphBuilder(AnalysisGraph *ag)
        {
            this->analysis_graph = ag;
        }

        unique_ptr<Graph> build()
        {
            log.ext_trace("[{}] init", __func__);

            map<string, unique_ptr<SimModelNode>> models;

            for (auto &[ssp_resource_name, model] : analysis_graph->models)
            {

                auto m = make_unique<SimModelNode>(ssp_resource_name, model->fmu);

                log.trace("[{}] New Model: {}", __func__, m->name);
                models[m->name] = std::move(m);
            }

            for (auto &[ssp_resource_name, model] : analysis_graph->models)
            {
                for (auto child : model->children)
                {
                    models[model->name]->add_child(models[child->name].get());
                }
            }

            log.ext_trace("[{}] exit", __func__);
            return make_unique<Graph>(std::move(models));
        }
    };

}
