#pragma once

#include "common_log.hpp"

#include "FMI2_Enums_Ext.hpp"

#include "analysis_graph.hpp"
#include "data_recorder.hpp"

#include "model_async.hpp"
#include "model_fmu.hpp"
#include "graph.hpp"

#include <map>

namespace ssp4cpp::sim::graph
{
    using AnalysisGraph = analysis::graph::AnalysisGraph;

    class GraphBuilder
    {
    public:
        static inline auto log = common::Logger("GraphBuilder", common::LogLevel::info);

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

            log.trace("[{}] - Create the fmu models", __func__);
            for (auto &[ssp_resource_name, analysis_model] : analysis_graph->models)
            {
                auto m = make_unique<FmuModel>(ssp_resource_name, analysis_model->fmu);
                m->recorder = recorder;
                log.ext_trace("[{}] -- New Model: {}", __func__, m->name);
                models[analysis_model->name] = std::move(m);
            }

            log.trace("[{}] - Create the data storage areas within the model", __func__);
            for (auto &[_, analysis_model] : analysis_graph->models)
            {
                auto model = models[analysis_model->name].get();
                for (auto &[name, connector] : analysis_model->connectors)
                {
                    int index = -1;
                    if (connector->causality == Causality::input)
                        index = model->input_area->add(name, connector->type, connector->forward_derivatives_order);
                    else if (connector->causality == Causality::output)
                        index = model->output_area->add(name, connector->type, connector->forward_derivatives_order);

                    ConnectorInfo info;
                    info.type = connector->type;
                    info.size = connector->size;
                    info.name = name;

                    info.forward_derivatives = connector->forward_derivatives;
                    info.forward_derivatives_order = connector->forward_derivatives_order;

                    info.index = index;
                    info.value_ref = connector->value_reference;

                    info.fmu = model->fmu;

                    if (connector->initial_value)
                    {
                        info.initial_value = connector->initial_value->get_value();

                        log.debug("[{}] -- Store start value for {} : {}", __func__, info.name, fmi2::ext::enums::data_type_to_string(info.type, (void *)info.initial_value.get()));
                    }

                    if (connector->causality == Causality::input)
                    {
                        info.storage = model->input_area.get();
                        model->inputs[name] = std::move(info);
                    }
                    else if (connector->causality == Causality::output)
                    {
                        info.storage = model->output_area.get();
                        model->outputs[name] = std::move(info);
                    }
                    else if (connector->causality == Causality::parameter)
                        model->parameters[name] = std::move(info);
                }
            }

            log.trace("[{}] - Hand the information regarding the connections over to the model", __func__);
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

                con_info.forward_derivatives = source_connector.forward_derivatives;
                con_info.forward_derivatives_order = source_connector.forward_derivatives_order;

                // the target is responsible for copying the connection
                target_model->connections.push_back(std::move(con_info));
            }

            log.trace("[{}] - Allocate the input/output areas", __func__);
            for (auto &[ssp_resource_name, model] : models)
            {
                model->input_area->allocate();
                model->output_area->allocate();
                recorder->add_storage(model->input_area->data.get());
                recorder->add_storage(model->output_area->data.get());
            }

            log.trace("[{}] - Wrap models in async", __func__);
            std::map<std::string, std::unique_ptr<AsyncNode>> async_models;
            for (auto &[n, m] : models)
            {
                auto name = m->name;
                async_models[name] = std::make_unique<AsyncNode>(name, std::move(m));
            }

            log.trace("[{}] - Create connections between models", __func__);
            for (auto &[_, analysis_model] : analysis_graph->models)
            {
                for (auto &child : analysis_model->children)
                {
                    async_models[analysis_model->name]->add_child(async_models[child->name].get());
                }
            }

            // break algebraic loops here... or before they are connected....
            // Add a delay of a minor time amount to make sure that the broken loop cant use data that is to new

            // do something fancy with the graph

            log.ext_trace("[{}] exit", __func__);
            return std::make_unique<Graph>(std::move(async_models));
        }
    };

}
