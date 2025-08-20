#pragma once
#pragma once

#include "common_log.hpp"


#include "analysis_graph.hpp"

#include "model.hpp"
#include "graph.hpp"

#include <map>





namespace ssp4cpp::sim::graph
{
    using AnalysisGraph = analysis::graph::AnalysisGraph;

    class GraphBuilder
    {
    public:
        static inline auto log = common::Logger("sim::graph::GraphBuilder", common::LogLevel::info);

        AnalysisGraph *analysis_graph;

        GraphBuilder(AnalysisGraph *ag)
        {
            this->analysis_graph = ag;
        }

        unique_ptr<Graph> build()
        {
            log.ext_trace("[{}] init", __func__);

            std::map<string, unique_ptr<Model>> models;

            for (auto &[ssp_resource_name, model] : analysis_graph->models)
            {

                auto m = make_unique<Model>(ssp_resource_name, model->fmu);

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

            for (auto &[_, connection] : analysis_graph->connections)
            {
                auto source_connector = connection->source_connector;
                
                auto target_connector = connection->target_connector;
            }

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

            log.ext_trace("[{}] exit", __func__);
            return make_unique<Graph>(std::move(models));
        }
    };

}
