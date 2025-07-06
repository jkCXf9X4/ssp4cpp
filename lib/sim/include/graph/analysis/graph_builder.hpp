#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "fmu_handler.hpp"

#include "node_connection.hpp"
#include "node_model.hpp"
#include "node_connector.hpp"
#include "node_internal.hpp"

#include "analysis_graph.hpp"

#include "fmu.hpp"
#include "ssp_ext.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::analysis::graph
{
    using namespace std;

    class GraphBuilder
    {
    public:
        static inline auto log = common::Logger("sim::graph::GraphBuilder", common::LogLevel::info);

        ssp4cpp::Ssp *ssp;
        handler::FmuHandler *fmu_handler

        GraphBuilder(ssp4cpp::Ssp *ssp, handler::FmuHandler *fmu_handler)
        {
            this->ssp = ssp;
            this->fmu_handler = fmu_handler;
        }

        map<string, unique_ptr<ModelNode>> create_models(ssp4cpp::Ssp &ssp)
        {
            log.ext_trace("[{}] init", __func__);
            map<string, unique_ptr<ModelNode>> models;
            for (auto &[ssp_resource_name, local_resource_name] : ssp::ext::get_resources(ssp))
            {
                auto m = make_unique<ModelNode>(ssp_resource_name, local_resource_name);
                log.trace("[{}] New Model: {}", __func__, m->name);
                models[m->name] = std::move(m);
            }
            log.ext_trace("[{}] exit", __func__);
            return std::move(models);
        }

        // Helper: create_variable with explicit type and context
        std::unique_ptr<ConnectorNode> create_connector(std::string component_name,
                                                        std::string connector_name)
        {
            using namespace handler;

            auto fmu = fmu_handler->fmus[component_name].get();

            auto md = fmu->model_description;
            auto var = md->get_variable_by_name(connector_name);

            auto value_reference = var.value_reference;
            auto type = utils::get_variable_type(var);

            return std::make_unique<ConnectorNode>(
                component_name, connector_name, value_reference, type);
        }

        map<string, unique_ptr<ConnectorNode>> create_connectors(ssp4cpp::Ssp &ssp)
        {
            log.ext_trace("[{}] init", __func__);
            map<string, unique_ptr<ConnectorNode>> items;
            if (ssp.ssd.System.Elements.has_value())
            {
                auto connectors = ssp1::ext::elements::get_connectors(
                    ssp.ssd.System.Elements.value(),
                    {ssp4cpp::fmi2::md::Causality::input, ssp4cpp::fmi2::md::Causality::output});

                for (auto &[index, connector, component] : connectors)
                {
                    auto component_name = component->name.value();
                    auto connector_name = connector->name;

                    auto c = create_connector(component_name, connector_name);
                    log.trace("[{}] New Connector: {}", __func__, c->name);
                    items[c->name] = std::move(c);
                }
            }
            log.ext_trace("[{}] exit, Total connectors created: {}", __func__, items.size());
            return std::move(items);
        }

        map<string, unique_ptr<ConnectionNode>> create_connections(ssp4cpp::Ssp &ssp)
        {
            log.ext_trace("[{}] init", __func__);
            map<string, unique_ptr<ConnectionNode>> items;
            for (auto &connection : ssp.ssd.System.Connections.value().Connections)
            {
                auto c = make_unique<ConnectionNode>(&connection);
                log.trace("[{}] New Connection: {}", __func__, c->name);
                items[c->name] = std::move(c);
            }
            log.ext_trace("[{}] exit, Total connections created: {}", __func__, items.size());
            return std::move(items);
        }

        map<string, unique_ptr<ModelVariableNode>> create_model_variables(map<string, ssp4cpp::Fmu *> &fmu_map)
        {
            log.warning("[{}] init, deprecated", __func__);
            map<string, unique_ptr<ModelVariableNode>> items;
            for (auto [name, fmu] : fmu_map)
            {
                for (auto &variable : fmu->md.ModelVariables.ScalarVariable)
                {
                    auto mv = make_unique<ModelVariableNode>(name, variable.name);
                    log.trace("[{}] New ModelVariable: {}", __func__, mv->name);
                    items[mv->name] = std::move(mv);
                }
            }

            log.ext_trace("[{}] exit, Total model variables created: {}", __func__, items.size());
            return std::move(items);
        }

        unique_ptr<Graph> build()
        {
            log.ext_trace("[{}] init", __func__);
            auto models = create_models(*ssp);
            auto connectors = create_connectors(*ssp);
            auto connections = create_connections(*ssp);

            auto fmu_connections = ssp1::ext::elements::get_fmu_connections(ssp->ssd);

            log.debug("[{}] Connecting FMUs", __func__);
            for (auto &[source, target] : fmu_connections)
            {
                log.debug("[{}] Connecting: {} -> {}", __func__, source, target);
                models[source]->add_child(models[target].get());
            }

            log.debug("[{}] Connecting connectors", __func__);
            for (auto &[name, c] : connections)
            {
                log.debug("[{}] Connecting {}", __func__, c->name);

                auto source_model = models[c->start_component].get();
                auto target_model = models[c->end_component].get();

                auto source_connector_name = c->get_source_connector_name();
                auto target_connector_name = c->get_target_connector_name();

                auto source_connector = connectors[source_connector_name].get();
                auto target_connector = connectors[target_connector_name].get();

                source_model->connectors.output_connectors[source_connector_name] = source_connector;
                target_model->connectors.input_connectors[target_connector_name] = target_connector;

                source_connector->add_child(c.get());
                c->add_child(target_connector);

                auto ref = source_connector->create_data_storage();
                target_connector->data_reference = ref;
            }

            // possible to add internal connections as well
            // see below

            log.ext_trace("[{}] exit", __func__);
            return make_unique<Graph>(std::move(models), std::move(connectors), std::move(connections));
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
