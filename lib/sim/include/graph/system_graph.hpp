#include "common_map.hpp"

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

    using Node = common::graph::Node;

    map<string, Model *> get_new_models(map<string, Fmu *> &fmu_map)
    {
        log.ext_trace("[{}] init", __func__);
        map<string, Model *> models;
        for (auto &[str, fmu] : fmu_map)
        {
            log.debug("[{}] New model: {}", __func__, str);
            models[str] = new Model(str, fmu);
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

    vector<Node *> create_system_graph(Ssp &ssp, map<string, Fmu *> &fmu_map)
    {
        log.ext_trace("[{}] init", __func__);
        auto models = get_new_models(fmu_map);

        auto fmu_connections = ssp1::ext::elements::get_fmu_connections(ssp.ssd);

        for (auto &[source, target] : fmu_connections)
        {
            log.debug("[{}] Connecting: {} -> {}", __func__, source, target);
            models[source]->add_child(models[target]);
        }

        auto m = ssp4cpp::common::map_ns::map_to_value_vector_copy(models);
        auto n = Model::cast_to_parent_ptrs(m);
        log.ext_trace("[{}] exit", __func__);
        return n;
    }

    vector<Node *> create_connection_graph(Ssp &ssp, map<string, Fmu *> &fmu_map)
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

            auto source_connector = connectors[Connector::create_name(c->start_component, c->start_connector)];
            auto target_connector = connectors[Connector::create_name(c->end_component, c->end_connector)];

            auto connection_name = Connection::create_name(
                c->start_component, c->start_connector,
                c->end_component, c->end_connector);
            auto connection = connections[connection_name];

            source_model->add_child(source_connector);
            source_connector->add_child(connection);
            connection->add_child(target_connector);
            target_connector->add_child(target_model);
        }
        
        auto m = ssp4cpp::common::map_ns::map_to_value_vector_copy(models);
        auto n = Model::cast_to_parent_ptrs(m);
        log.ext_trace("[{}] exit", __func__);
        return n;

        // all connectors that are not used are leaking memory, for small models this is okey - evaluate for larger models
    }
}