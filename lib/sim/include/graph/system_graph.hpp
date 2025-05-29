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

    inline auto log = common::Logger("sim::graph", common::LogLevel::debug);

    using Node = common::graph::Node;

    map<string, Model *> get_new_models(map<string, Fmu *> &fmu_map)
    {
        map<string, Model *> models;
        for (auto &[str, fmu] : fmu_map)
        {
            log.debug("[{}] New model: {}", __func__, str);
            models[str] = new Model(str, fmu);
        }
        return models;
    }

    map<string, Connector *> get_new_connectors(ssp4cpp::Ssp &ssp)
    {
        map<string, Connector *> items;
        if (ssp.ssd.System.Elements.has_value())
        {
            auto connectors = ssp1::ext::elements::get_connectors(
                ssp.ssd.System.Elements.value(),
                {ssp4cpp::fmi2::md::Causality::input, ssp4cpp::fmi2::md::Causality::output});

            for (auto &[index, connector, component] : connectors)
            {
                auto c = new Connector(component->name.value(), connector);
                log.debug("[{}] New Connector: {}", __func__, c->name);
                items[c->name] = c;
            }
        }
        log.debug("[{}] Total connectors created: {}", __func__, items.size());
        return items;
    }

    map<string, Connection *> get_new_connections(ssp4cpp::Ssp &ssp)
    {
        map<string, Connection*> items;     
        for (auto &connection : ssp.ssd.System.Connections.value().Connections)
        {
            auto c = new Connection(&connection);
            items[c->name] = c;
        }
        log.debug("[{}] Total connections created: {}", __func__, items.size());
        return items;
    }

    vector<Node *> create_system_graph(Ssp &ssp, map<string, Fmu *> &fmu_map)
    {
        auto models = get_new_models(fmu_map);

        auto fmu_connections = ssp1::ext::elements::get_fmu_connections(ssp.ssd);

        for (auto &[source, target] : fmu_connections)
        {
            log.debug("Connection: {} -> {}", source, target);
            models[source]->add_child(models[target]);
        }

        auto m = ssp4cpp::common::map_ns::map_to_value_vector_copy(models);
        return Model::cast_to_parent_ptrs(m);
    }

    vector<Model *> create_connection_graph(Ssp &ssp, map<string, Fmu *> &fmu_map)
    {
        log.debug("[{}] init", __func__);
        log.debug("[{}] Get models", __func__);
        auto models = get_new_models(fmu_map);
        log.debug("[{}] Get connectors", __func__);
        auto connectors = get_new_connectors(ssp);
        log.debug("[{}] Get connections", __func__);
        auto connections = get_new_connections(ssp);

        log.debug("[{}] Start linking", __func__);
        for (auto &[name, connection] : connections)
        {
            log.debug("[{}] Linking {}", __func__, connection->name);
        }

        vector<Model *> n;
        return n;

        // all connectors that are not used are leaking memory, for small models this is okey - evaluate for larger models
    }
}