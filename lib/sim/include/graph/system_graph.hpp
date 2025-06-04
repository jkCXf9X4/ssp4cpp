#include "common_map.hpp"
#include "common_list.hpp"

#include "connection.hpp"
#include "ssp_ext.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::graph
{
    using namespace std;

    inline auto log = common::Logger("sim::graph", common::LogLevel::ext_trace);

    using SimNode = sim::graph::SimNode;

    map<string, Model *> get_new_models(map<string, Fmu *> &fmu_map)
    {
        log.ext_trace("[{}] init", __func__);
        map<string, Model *> models;
        for (auto &[str, fmu] : fmu_map)
        {
            auto m = new Model(str, fmu);
            log.trace("[{}] New Model: {}", __func__, m->name);

            models[m->name] = m;
        }
        log.ext_trace("[{}] exit", __func__);
        return models;
    }

    map<string, Connector *> get_new_connectors(ssp4cpp::Ssp &ssp)
    {
        log.ext_trace("[{}] init", __func__);
        map<string, Connector *> items;
        if (ssp.ssd.System.Elements.has_value())
        {
            auto connectors = ssp1::ext::elements::get_connectors(
                ssp.ssd.System.Elements.value(),
                {ssp4cpp::fmi2::md::Causality::input, ssp4cpp::fmi2::md::Causality::output});

            for (auto &[index, connector, component] : connectors)
            {
                auto c = new Connector(component->name.value(), connector);
                log.trace("[{}] New Connector: {}", __func__, c->name);
                items[c->name] = c;
            }
        }
        log.ext_trace("[{}] exit, Total connectors created: {}", __func__, items.size());
        return items;
    }

    map<string, Connection *> get_new_connections(ssp4cpp::Ssp &ssp)
    {
        log.ext_trace("[{}] init", __func__);
        map<string, Connection *> items;
        for (auto &connection : ssp.ssd.System.Connections.value().Connections)
        {
            auto c = new Connection(&connection);
            log.trace("[{}] New Connection: {}", __func__, c->name);
            items[c->name] = c;
        }
        log.ext_trace("[{}] exit, Total connections created: {}", __func__, items.size());
        return items;
    }

    map<string, ModelVariable *> get_new_model_variables(map<string, Fmu *> &fmu_map)
    {
        log.ext_trace("[{}] init", __func__);
        map<string, ModelVariable *> items;
        for (auto [name, fmu] : fmu_map)
        {
            for (auto &variable : fmu->md.ModelVariables.ScalarVariable)
            {
                auto mv = new ModelVariable(name, variable.name);
                log.trace("[{}] New ModelVariable: {}", __func__, mv->name);
                items[mv->name] = mv;
            }
        }

        log.ext_trace("[{}] exit, Total model variables created: {}", __func__, items.size());
        return items;
    }

    vector<SimNode *> remove_dangling(vector<SimNode *> nodes)
    {
        vector<SimNode *> out;
        for (auto &n : nodes)
        {
            if (n->is_orphan())
            {
                log.ext_trace("[{}] Deleting {}", __func__, n->name);
                delete n;
            }
            else
            {
                out.push_back(n);
            }
        }
        return out;
    }

    vector<SimNode *> create_system_graph(Ssp &ssp, map<string, Fmu *> &fmu_map)
    {
        log.ext_trace("[{}] init", __func__);
        auto models = get_new_models(fmu_map);

        auto fmu_connections = ssp1::ext::elements::get_fmu_connections(ssp.ssd);

        for (auto &[source, target] : fmu_connections)
        {

            log.debug("[{}] Connecting: {} -> {}", __func__, source, target);
            models[source]->add_child(models[target]);
        }
        vector<SimNode *> output;
        for (auto &[_, model] : models)
            output.push_back(model);
        auto o = remove_dangling(output);

        log.ext_trace("[{}] exit", __func__);
        return o;
    }

    vector<SimNode *> create_connection_graph(Ssp &ssp, map<string, Fmu *> &fmu_map)
    {
        log.ext_trace("[{}] init", __func__);
        auto models = get_new_models(fmu_map);
        auto connectors = get_new_connectors(ssp);
        auto connections = get_new_connections(ssp);

        log.debug("[{}] Start Connecting", __func__);
        for (auto &[name, c] : connections)
        {
            log.debug("[{}] Connecting {}", __func__, c->name);

            auto source_model = models[c->start_component];
            auto target_model = models[c->end_component];

            auto source_connector = connectors[c->get_source_connector_name()];
            auto target_connector = connectors[c->get_target_connector_name()];

            source_model->add_child(source_connector);
            source_connector->add_child(c);
            c->add_child(target_connector);
            target_connector->add_child(target_model);
        }

        vector<SimNode *> output;
        for (auto &[_, model] : models)
            output.push_back(model);
        for (auto &[_, connector] : connectors)
            output.push_back(connector);
        for (auto &[_, connection] : connections)
            output.push_back(connection);
        auto o = remove_dangling(output);

        log.ext_trace("[{}] exit", __func__);
        return o;

        // all connectors that are not used are leaking memory, for small models this is okey - evaluate for larger models
    }

    vector<SimNode *> create_feedthrough_graph(Ssp &ssp, map<string, Fmu *> &fmu_map)
    {
        log.ext_trace("[{}] init", __func__);
        auto models = get_new_models(fmu_map);
        auto connectors = get_new_connectors(ssp);
        auto connections = get_new_connections(ssp);

        auto variables = get_new_model_variables(fmu_map);

        log.debug("[{}] Connecting fmus", __func__);
        for (auto &[name, c] : connections)
        {
            log.debug("[{}] Connecting {}", __func__, c->name);

            auto source_connector = connectors[c->get_source_connector_name()];
            auto target_connector = connectors[c->get_target_connector_name()];

            source_connector->add_child(c);
            c->add_child(target_connector);
        }

        log.new_line();

        for (auto [fmu_name, fmu] : fmu_map)
        {
            log.debug("[{}] Connecting internal dependencies, FMU:{}", __func__, fmu_name);

            auto outputs = fmu->md.ModelStructure.Outputs;
            if (outputs.has_value())
            {

                auto dependencies = ssp4cpp::fmi2::ext::dependency::get_dependencies_variables(
                    outputs.value().Unknowns,
                    fmu->md.ModelVariables,
                    ssp4cpp::fmi2::md::DependenciesKind::dependent);

                for (auto &[source, target, kind] : dependencies)
                {
                    auto source_id = Connector::create_name(fmu_name, source->name);
                    auto target_id = Connector::create_name(fmu_name, target->name);
                    SimNode *source_node;
                    SimNode *target_node;

                    // The connections can be from connectors or variables, maybe...
                    if (connectors.contains(source_id))
                    {
                        source_node = connectors[source_id];
                        log.debug("[{}] Source C {}", __func__, connectors[source_id]->name);
                    }
                    else
                    {
                        source_node = variables[source_id];
                        log.debug("[{}] Source V {}", __func__, variables[source_id]->name);
                    }

                    if (connectors.contains(target_id))
                    {
                        target_node = connectors[target_id];
                        log.debug("[{}] Target C {}", __func__, connectors[target_id]->name);
                    }
                    else
                    {
                        target_node = variables[target_id];
                        log.debug("[{}] Target V {}", __func__, variables[target_id]->name);
                    }
                    log.debug("[{}] Connecting {} -> {}", __func__, source_node->name, target_node->name);
                    source_node->add_child(target_node);
                }
            }
        }

        vector<SimNode *> output;
        for (auto &[_, model] : models)
            output.push_back(model);
        for (auto &[_, connector] : connectors)
            output.push_back(connector);
        for (auto &[_, connection] : connections)
            output.push_back(connection);
        for (auto &[_, variable] : variables)
            output.push_back(variable);
        auto o = remove_dangling(output);

        log.ext_trace("[{}] exit", __func__);
        return o;
    }
}
