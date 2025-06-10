#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "data_handler.hpp"
#include "fmu_handler.hpp"
#include "variable_handler.hpp"

#include "node_connection.hpp"
#include "node_model.hpp"
#include "node_connector.hpp"

#include "graph.hpp"

#include "ssp_ext.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::graph
{
    using namespace std;

    class GraphBuilder
    {
    public:
        static inline auto log = common::Logger("sim::graph::GraphBuilder", common::LogLevel::ext_trace);

        ssp4cpp::Ssp *ssp;
        handler::FmuHandler *fmu_handler;
        handler::VariableHandler *variable_handler;
        handler::DataHandler *data_handle;

        GraphBuilder()
        {
        }

        GraphBuilder *set_ssp(ssp4cpp::Ssp *ssp)
        {
            this->ssp = ssp;
            return this;
        }

        GraphBuilder *set_fmu_handler(sim::FmuHandler *fmu_handler)
        {
            this->fmu_handler = fmu_handler;
            return this;
        }

        GraphBuilder *set_variable_handler(sim::VariableHandler *variable_handler)
        {
            this->variable_handler = variable_handler;
            return this;
        }

        GraphBuilder *set_data_handler(sim::data::DataHandler *data_handler)
        {
            this->data_handler = data_handler;
            return this;
        }

        map<string, unique_ptr<Model>> create_models(ssp4cpp::Ssp &ssp)
        {
            log.ext_trace("[{}] init", __func__);
            map<string, unique_ptr<Model>> models;
            for (auto &[ssp_resource_name, local_resource_name] : ssp::ext::get_resources(ssp))
            {
                auto m = make_unique<Model>(ssp_resource_name, local_resource_name);
                log.trace("[{}] New Model: {}", __func__, m->name);

                models[m->name] = std::move(m);
            }
            log.ext_trace("[{}] exit", __func__);
            return std::move(models);
        }

        map<string, unique_ptr<Connector>> create_connectors(ssp4cpp::Ssp &ssp)
        {
            log.ext_trace("[{}] init", __func__);
            map<string, unique_ptr<Connector>> items;
            if (ssp.ssd.System.Elements.has_value())
            {
                auto connectors = ssp1::ext::elements::get_connectors(
                    ssp.ssd.System.Elements.value(),
                    {ssp4cpp::fmi2::md::Causality::input, ssp4cpp::fmi2::md::Causality::output});

                for (auto &[index, connector, component] : connectors)
                {
                    auto c = make_unique<Connector>(component->name.value(), connector->name);
                    log.trace("[{}] New Connector: {}", __func__, c->name);
                    items[c->name] = std::move(c);
                }
            }
            log.ext_trace("[{}] exit, Total connectors created: {}", __func__, items.size());
            return std::move(items);
        }

        map<string, unique_ptr<Connection>> create_connections(ssp4cpp::Ssp &ssp)
        {
            log.ext_trace("[{}] init", __func__);
            map<string, unique_ptr<Connection>> items;
            for (auto &connection : ssp.ssd.System.Connections.value().Connections)
            {
                auto c = make_unique<Connection>(&connection);
                log.trace("[{}] New Connection: {}", __func__, c->name);
                items[c->name] = std::move(c);
            }
            log.ext_trace("[{}] exit, Total connections created: {}", __func__, items.size());
            return std::move(items);
        }

        map<string, unique_ptr<ModelVariable>> create_model_variables(map<string, Fmu *> &fmu_map)
        {
            log.warning("[{}] init, deprecated", __func__);
            map<string, unique_ptr<ModelVariable>> items;
            for (auto [name, fmu] : fmu_map)
            {
                for (auto &variable : fmu->md.ModelVariables.ScalarVariable)
                {
                    auto mv = make_unique<ModelVariable>(name, variable.name);
                    log.trace("[{}] New ModelVariable: {}", __func__, mv->name);
                    items[mv->name] = std::move(mv);
                }
            }

            log.ext_trace("[{}] exit, Total model variables created: {}", __func__, items.size());
            return std::move(items);
        }

        Graph build()
        {
            log.ext_trace("[{}] init", __func__);
            auto models = create_models(ssp);
            auto connectors = create_connectors(ssp);
            auto connections = create_connections(ssp);

            auto fmu_connections = ssp1::ext::elements::get_fmu_connections(ssp.ssd);

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

                source_model->output_connector[source_connector_name] = source_connector;
                source_model->input_connector[target_connector_name] = source_connector;

                source_connector->add_child(c.get());
                c->add_child(target_connector);
            }

            // possible to add internal connections as well
            // see below

            log.ext_trace("[{}] exit", __func__);
            auto system = Graph(std::move(models), std::move(connectors), std::move(connections));
            return std::move(system);
        }
    };

}

// vector<AnalysisNode *> create_feedthrough_graph(ssp4cpp::Ssp &ssp, map<string, Fmu *> &fmu_map)
// {
//     log.ext_trace("[{}] init", __func__);
//     auto models = get_new_models(*ssp);
//     auto connectors = get_new_connectors(*ssp);
//     auto connections = get_new_connections(*ssp);

//     auto variables = get_new_model_variables(fmu_map);

//     log.debug("[{}] Connecting fmus", __func__);
//     for (auto &[name, c] : connections)
//     {
//         log.debug("[{}] Connecting {}", __func__, c->name);

//         auto source_connector = connectors[c->get_source_connector_name()];
//         auto target_connector = connectors[c->get_target_connector_name()];

//         source_connector->add_child(c);
//         c->add_child(target_connector);
//     }

//     log.new_line();

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

//     vector<SimNode *> output;
//     for (auto &[_, model] : models)
//         output.push_back(model);
//     for (auto &[_, connector] : connectors)
//         output.push_back(connector);
//     for (auto &[_, connection] : connections)
//         output.push_back(connection);
//     for (auto &[_, variable] : variables)
//         output.push_back(variable);
//     auto o = remove_dangling(output);

//     log.ext_trace("[{}] exit", __func__);
//     return o;
// }
