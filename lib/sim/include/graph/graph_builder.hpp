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

            // create the models
            for (auto &[ssp_resource_name, analysis_model] : analysis_graph->models)
            {
                auto m = make_unique<Model>(ssp_resource_name, analysis_model->fmu);

                log.trace("[{}] New Model: {}", __func__, m->name);
                models[analysis_model->name] = std::move(m);
            }

            // Connect the models
            for (auto &[_, analysis_model] : analysis_graph->models)
            {
                for (auto &child : analysis_model->children)
                {
                    models[analysis_model->name]->add_child(models[child->name].get());
                }
            }

            // Create the data storage areas within the model
            for (auto &[_, analysis_model] : analysis_graph->models)
            {
                auto model = models[analysis_model->name].get();
                for (auto &[name, connector] : analysis_model->input_connectors)
                {
                    auto index = model->input_area->add(name, connector->type);

                    ConnectorInfo info;
                    info.type = connector->type;
                    info.size = connector->size;
                    info.name = name;

                    info.index = index;
                    info.value_ref = connector->value_reference;

                    model->inputs[name] = std::move(info);
                }

                for (auto &[name, connector] : analysis_model->output_connectors)
                {
                    auto index = model->output_area->add(name, connector->type);

                    ConnectorInfo info;
                    info.type = connector->type;
                    info.size = connector->size;
                    info.name = name;

                    info.index = index;
                    info.value_ref = connector->value_reference;

                    model->outputs[name] = std::move(info);
                }
            }

            // Hand the information regarding the connections over to the model
            for (auto &[_, connection] : analysis_graph->connections)
            {
                auto source_model = models[connection->source_model->name].get();
                auto target_model = models[connection->target_model->name].get();

                auto source_connector = source_model->outputs[connection->get_source_connector_name()];
                auto target_connector = target_model->inputs[connection->get_target_connector_name()];

                ConnectionInfo con_info;
                con_info.type = source_connector.type;
                con_info.size = source_connector.size;

                con_info.source_storage = source_model->output_area.get();
                con_info.target_storage = target_model->input_area.get();
                con_info.source_index = source_connector.index;
                con_info.target_index = target_connector.index;

                // the target is responsible for copying the connection
                target_model->connections.push_back(con_info);
            }

            // Allocate the input/output areas
            for (auto &[ssp_resource_name, model] : models)
            {
                model->input_area->allocate();
                model->output_area->allocate();
            }

            log.ext_trace("[{}] exit", __func__);
            return make_unique<Graph>(std::move(models));
        }
    };

}
