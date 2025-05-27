

#include "ssp.hpp"
#include "fmu.hpp"
#include "common_io.hpp"
#include "common_log.hpp"
#include "common_string.hpp"
#include "common_node.hpp"
#include "tarjan.hpp"

#include "SSP1_SystemStructureDescription_Ext.hpp"
#include "FMI2_modelDescription_Ext.hpp"

#include "connection.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

using namespace std;
using namespace ssp4cpp;
using namespace common::io;
using namespace common;

int main()
{
    auto log = Logger("sim.main", LogLevel::debug);
    log.debug("Opening SSP");

    auto ssp = ssp4cpp::Ssp("./resources/algebraic_loop_4.ssp");

    log.debug("SSP: {}", ssp.to_string());

    auto fmus = map<string, sim::graph::Model>();
    for (auto &resource : ssp4cpp::ssp1::ext::ssd::get_resources(ssp.ssd))
    {
        auto name = resource->name.value_or("null");
        log.debug("Resource {}", name);
        
        auto fmu = ssp4cpp::Fmu(ssp.temp_dir / resource->source);
        auto fmu_node = sim::graph::Model(name, fmu);
        fmus[name] = fmu_node;
    }
    
    log.debug("Map {}", common::str::to_str(fmus));

    auto fmu_connections = set<pair<string, string>>();

    for (auto connection : ssp.ssd.System.Connections.value().Connections)
    {
        auto p = std::make_pair(connection.startElement.value(), connection.endElement.value());
        fmu_connections.insert(p);

        // auto start = connection.startElement.value() + "." + connection.startConnector;
        // auto end = connection.endElement.value() + "." + connection.endConnector;

        // cout << start << ": " << connector_str_int_map[start] << " -> " << end << ": " << connector_str_int_map[end] << endl;
    }

    graph::Node* model;
    for (auto &[source, target] : fmu_connections)
    {
        log.debug("Connection: {} -> {}", source, target);
        fmus[source].add_child(&fmus[target]);
        model = &fmus[source];
    }

    log.info("DOT \n{}", model->to_dot());
    auto nodes = model->all_nodes();


    auto ssc = common::graph::strongly_connected_components(nodes);
    log.info("{}", common::graph::ssc_to_string(ssc));





    // initilize all

    // execute graph
    /*
    execute fmus in order for each timestep
    - this wont work with the timestamp approach. new data will not be available

    before fmu execution
    getData -> setVariable

    execute fmu

    After each fmu execution
    getVariable ->  setData


    */

    std::cout << "Parsing complete\n";
    return 0;
}
