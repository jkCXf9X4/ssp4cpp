#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "SSP_Ext.hpp"
#include "FMI2_modelDescription_Ext.hpp"

#include "fmu_handler.hpp"

#include "analysis_connection.hpp"
#include "analysis_model.hpp"
#include "analysis_connector.hpp"
#include "analysis_internal.hpp"

#include "analysis_graph.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::analysis::graph
{
    using namespace std;

    class AnalysisGraphBuilder
    {
    public:
        static inline auto log = common::Logger("analysis::graph::AnalysisGraphBuilder", common::LogLevel::info);

        ssp4cpp::Ssp *ssp;
        handler::FmuHandler *fmu_handler;

        AnalysisGraphBuilder(ssp4cpp::Ssp *ssp, handler::FmuHandler *fmu_handler)
        {
            this->ssp = ssp;
            this->fmu_handler = fmu_handler;
        }

        map<string, std::unique_ptr<AnalysisModel>> create_models(ssp4cpp::Ssp &ssp)
        {
            log.ext_trace("[{}] init", __func__);
            map<string, std::unique_ptr<AnalysisModel>> models;
            for (auto &[ssp_resource_name, local_resource_name] : ssp::ext::get_resource_map(ssp))
            {
                auto fmu = fmu_handler->fmu_info_map[ssp_resource_name].get();
                auto m = make_unique<AnalysisModel>(ssp_resource_name, local_resource_name, fmu);

                log.trace("[{}] New Model: {}", __func__, m->name);
                models[m->name] = std::move(m);
            }
            log.ext_trace("[{}] exit", __func__);
            return std::move(models);
        }

        // Helper: create_variable with explicit type and context
        std::unique_ptr<AnalysisConnector> create_connector(std::string component_name,
                                                            std::string connector_name,
                                                            Causality &causality)
        {
        }

        map<string, std::unique_ptr<AnalysisConnector>> create_connectors(ssp4cpp::Ssp &ssp)
        {
            log.ext_trace("[{}] init", __func__);
            map<string, std::unique_ptr<AnalysisConnector>> items;
            if (ssp.ssd->System.Elements.has_value())
            {
                auto connectors = ssp1::ext::elements::get_connectors(
                    ssp.ssd->System.Elements.value(),
                    {ssp4cpp::fmi2::md::Causality::input, ssp4cpp::fmi2::md::Causality::output, ssp4cpp::fmi2::md::Causality::parameter});

                for (auto &[index, connector, component] : connectors)
                {
                    auto component_name = component->name.value();
                    auto connector_name = connector->name;
                    log.trace("[{}] Creating Connector: {} - {}", __func__, component_name, connector_name);

                    // using namespace handler;

                    auto fmu = fmu_handler->fmu_info_map[component_name].get();

                    auto md = fmu->model_description;

                    log.ext_trace("[{}] get_variable_by_name", __func__);
                    auto var = fmi2::ext::model_variables::get_variable_by_name(md->ModelVariables, connector_name);
                    if (var)
                    {
                        auto value_reference = var->valueReference.value();
                        log.ext_trace("[{}] get_variable_type", __func__);
                        auto type = fmi2::ext::model_variables::get_variable_type(*var);

                        log.ext_trace("[{}] Create AnalysisConnector", __func__);
                        auto c = std::make_unique<AnalysisConnector>(
                            component_name, connector_name, value_reference, type);

                        c->causality = connector->kind;

                        if (c->causality == Causality::input)
                        {
                            auto start_value = fmi2::ext::model_variables::get_variable_start_value(*var);
                            if (start_value)
                            {
                                log.info("[{}] Storing start value for {}", __func__, var->name);
                                c->store_initial_value(start_value);
                            }
                        }

                        items[c->name] = std::move(c);
                    }
                }
            }
            log.ext_trace("[{}] exit, Total connectors created: {}", __func__, items.size());
            return std::move(items);
        }

        map<string, std::unique_ptr<AnalysisConnection>> create_connections(ssp4cpp::Ssp &ssp)
        {
            log.ext_trace("[{}] init", __func__);
            map<string, std::unique_ptr<AnalysisConnection>> items;
            if (ssp.ssd->System.Connections.has_value())
            {
                for (auto &connection : ssp.ssd->System.Connections.value().Connections)
                {
                    auto c = make_unique<AnalysisConnection>(&connection);
                    log.trace("[{}] New Connection: {}", __func__, c->name);
                    items[c->name] = std::move(c);
                }
            }
            log.ext_trace("[{}] exit, Total connections created: {}", __func__, items.size());
            return std::move(items);
        }

        map<string, std::unique_ptr<AnalysisModelVariable>> create_model_variables(map<string, ssp4cpp::Fmu *> &fmu_map)
        {
            log.warning("[{}] init, deprecated", __func__);
            map<string, std::unique_ptr<AnalysisModelVariable>> items;
            for (auto [name, fmu] : fmu_map)
            {
                for (auto &variable : fmu->md->ModelVariables.ScalarVariable)
                {
                    auto mv = make_unique<AnalysisModelVariable>(name, variable.name);
                    log.trace("[{}] New ModelVariable: {}", __func__, mv->name);
                    items[mv->name] = std::move(mv);
                }
            }

            log.ext_trace("[{}] exit, Total model variables created: {}", __func__, items.size());
            return std::move(items);
        }

        std::unique_ptr<AnalysisGraph> build()
        {
            log.trace("[{}] Building AnalysisGraph", __func__);
            auto models = create_models(*ssp);
            auto connectors = create_connectors(*ssp);
            auto connections = create_connections(*ssp);

            auto fmu_connections = ssp1::ext::elements::get_fmu_connections(*ssp->ssd);

            log.trace("[{}] Connecting FMUs", __func__);
            for (auto &[source, target] : fmu_connections)
            {
                log.trace("[{}] - Connecting: {} -> {}", __func__, source, target);
                models[source]->add_child(models[target].get());
            }

            log.trace("[{}] Attaching connectors to models", __func__);
            for (auto &[name, connector] : connectors)
            {
                auto model = models[connector->component_name].get();
                if (connector->causality == Causality::input)
                {
                    model->input_connectors[connector->name] = connector.get();
                }
                else if (connector->causality == Causality::output)
                {
                    model->output_connectors[connector->name] = connector.get();
                }
                else if (connector->causality == Causality::parameter)
                {
                    model->parameters[connector->name] = connector.get();
                }
                else
                {
                    log.error("[{}] Connector causality unknown", __func__);
                }
            }

            log.trace("[{}] Creating connections between connectors", __func__);
            for (auto &[name, connection] : connections)
            {
                log.trace("[{}] Connecting {}", __func__, connection->name);

                auto source_model = models[connection->source_component_name].get();
                auto target_model = models[connection->target_component_name].get();

                auto source_connector_name = connection->get_source_connector_name();
                auto target_connector_name = connection->get_target_connector_name();

                auto source_connector = connectors[source_connector_name].get();
                auto target_connector = connectors[target_connector_name].get();

                source_connector->model = source_model;
                target_connector->model = target_model;

                connection->source_connector = source_connector;
                connection->source_model = source_model;
                connection->target_connector = target_connector;
                connection->target_model = target_model;

                source_connector->add_child(connection.get());
                connection->add_child(target_connector);
            }

            // possible to add internal connections as well
            // see below

            log.ext_trace("[{}] exit", __func__);
            return make_unique<AnalysisGraph>(std::move(models), std::move(connectors), std::move(connections));
        }
    };

}

//     for (auto [fmu_name, fmu] : fmu_map)
//     {
//         log.debug("[{}] Connecting internal dependencies, FMU:{}", __func__, fmu_name);

//         auto outputs = fmu->md.ModelStructure.Outputs;
//         if (outputs.has_value())
//         {

//             auto dependencies = ssp4cpp::fmi2::ext::dependency::get_dependencies_variables(
//                 outputs.value().Unknowns,
//                 fmu->md.ModelVariables,
//                 ssp4cpp::fmi2::md::DependenciesKind::dependent);

//             for (auto &[source, target, kind] : dependencies)
//             {
//                 auto source_id = Connector::create_name(fmu_name, source->name);
//                 auto target_id = Connector::create_name(fmu_name, target->name);
//                 SimNode *source_node;
//                 SimNode *target_node;

//                 // The connections can be from connectors or variables, maybe...
//                 if (connectors.contains(source_id))
//                 {
//                     source_node = connectors[source_id];
//                     log.debug("[{}] Source C {}", __func__, connectors[source_id]->name);
//                 }
//                 else
//                 {
//                     source_node = variables[source_id];
//                     log.debug("[{}] Source V {}", __func__, variables[source_id]->name);
//                 }

//                 if (connectors.contains(target_id))
//                 {
//                     target_node = connectors[target_id];
//                     log.debug("[{}] Target C {}", __func__, connectors[target_id]->name);
//                 }
//                 else
//                 {
//                     target_node = variables[target_id];
//                     log.debug("[{}] Target V {}", __func__, variables[target_id]->name);
//                 }
//                 log.debug("[{}] Connecting {} -> {}", __func__, source_node->name, target_node->name);
//                 source_node->add_child(target_node);
//             }
//         }
//     }
