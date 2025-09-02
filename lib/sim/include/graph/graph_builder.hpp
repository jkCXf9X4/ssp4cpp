#pragma once

#include "common_log.hpp"

#include "analysis_graph.hpp"
#include "data_recorder.hpp"

#include "async_node.hpp"
#include "model_fmu.hpp"
#include "graph.hpp"

#include <map>

namespace ssp4cpp::sim::graph
{
    using AnalysisGraph = analysis::graph::AnalysisGraph;

    class GraphBuilder
    {
    public:
        static inline auto log = common::Logger("sim::graph::GraphBuilder", common::LogLevel::trace);

        AnalysisGraph *analysis_graph;
        utils::DataRecorder *recorder;

        GraphBuilder(AnalysisGraph *ag, utils::DataRecorder *recorder)
        {
            this->analysis_graph = ag;
            this->recorder = recorder;
        }

        std::unique_ptr<Graph> build()
        {
            log.trace("[{}] init", __func__);


            std::map<std::string, std::unique_ptr<FmuModel>> models;

            log.ext_trace("[{}] Create the fmu models", __func__);
            for (auto &[ssp_resource_name, analysis_model] : analysis_graph->models)
            {
                auto m = make_unique<FmuModel>(ssp_resource_name, analysis_model->fmu);
                m->recorder = recorder;
                log.trace("[{}] New Model: {}", __func__, m->name);
                models[analysis_model->name] = std::move(m);
            }

            log.ext_trace("[{}] Create the data storage areas within the model", __func__);
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

            log.ext_trace("[{}] Hand the information regarding the connections over to the model", __func__);
            for (auto &[_, connection] : analysis_graph->connections)
            {
                auto source_model = models[connection->source_model->name].get();
                auto target_model = models[connection->target_model->name].get();

                auto &source_connector = source_model->outputs[connection->get_source_connector_name()];
                auto &target_connector = target_model->inputs[connection->get_target_connector_name()];

                ConnectionInfo con_info;
                con_info.type = source_connector.type;
                con_info.size = source_connector.size;

                con_info.source_storage = source_model->output_area.get();
                con_info.target_storage = target_model->input_area.get();
                con_info.source_index = source_connector.index;
                con_info.target_index = target_connector.index;

                // the target is responsible for copying the connection
                target_model->connections.push_back(std::move(con_info));
            }

            log.ext_trace("[{}] Allocate the input/output areas", __func__);
            for (auto &[ssp_resource_name, model] : models)
            {
                model->input_area->allocate();
                model->output_area->allocate();
                recorder->add_storage(model->input_area->data.get());
                recorder->add_storage(model->output_area->data.get());

                // input push time 0
                // set possible input values from ssd/md
                // This is strange, why should initial values exist?
            }

            // store parameters that need to be set during init

            // Wrap models in async
            std::map<std::string, std::unique_ptr<InvocableNode>> async_models;
            for (auto &[n, m] : models)
            {
                auto name = m->name;
                async_models[name] = std::make_unique<AsyncNode>(name, std::move(m));
            }

            log.ext_trace("[{}] Create connections between models", __func__);
            for (auto &[_, analysis_model] : analysis_graph->models)
            {
                for (auto &child : analysis_model->children)
                {
                    async_models[analysis_model->name]->add_child(async_models[child->name].get());
                }
            }

            // do something fancy with the graph

            log.ext_trace("[{}] exit", __func__);
            return std::make_unique<Graph>(std::move(async_models));
        }
    };

}
