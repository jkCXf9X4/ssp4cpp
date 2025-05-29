#include "common_list.hpp"

#include "connection.hpp"
#include "ssp_ext.hpp"
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

    map<string, Node*> get_new_models(map<string, Fmu*> &fmu_map)
    {
        map<string, Node*> models;
        for (auto &[str, fmu] : fmu_map)
        {
            models[str] = new Model(str, fmu);
        }
        return models;
    }

    vector<Node*> create_system_graph(Ssp &ssp, map<string, Fmu*> &fmu_map)
    {
        auto models = get_new_models(fmu_map);

        auto fmu_connections = ssp1::ext::elements::get_fmu_connections(ssp.ssd);
        for (auto &[source, target] : fmu_connections)
        {
            log.debug("Connection: {} -> {}", source, target);
            models[source]->add_child(models[target]);
        }

        return ssp4cpp::common::list::map_to_value_vector_copy(models);

    }

    vector<Node*> create_connection_graph(Ssp &ssp, map<string, Fmu*> &fmu_map)
    {
        vector<Node*> nodes;
        return nodes;
        // auto models = get_new_models(fmu_map);

        // map<string, Node*> connectors;     
        // if (ssp.ssd.System.Elements.has_value())
        // {
        //     auto connectors = ssp1::ext::elements::get_connectors(
        //         ssp.ssd.System.Elements.value(),
        //         {ssp4cpp::fmi2::md::Causality::input, ssp4cpp::fmi2::md::Causality::output});

        //     for (auto &[index, connector, component] : connectors)
        //     {
        //         auto name = component->name.value() + "." + connector->name;
        //         connectors[name] = new Connector(connector->name, models[component->name.value()]);

        //     }
        // }


        // for (auto connection : ssp.ssd.System.Connections.value().Connections)
        // {
        //     auto start = connection.startElement.value() + "." + connection.startConnector;
        //     auto end = connection.endElement.value() + "." + connection.endConnector;

        //     add_edge(connector_str_int_map[start], connector_str_int_map[end], g);
        //     // cout << start << ": " << connector_str_int_map[start] << " -> " << end << ": " << connector_str_int_map[end] << endl;
        // }
        // return ssp4cpp::common::list::map_to_value_vector(models);

    }
}