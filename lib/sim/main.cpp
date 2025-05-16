

#include "ssp.hpp"
#include "fmu.hpp"
#include "common_io.hpp"
#include "common_log.hpp"
#include "common_string.hpp"

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
    log.debug("Opening ssp");

    auto ssp = ssp4cpp::Ssp("./resources/algebraic_loop_4.ssp");

    log.debug("Imported ssp! \n");
    log.debug("ssp: {}", ssp.to_str());

    // // Parsing FMI
    auto fmus = map<string, sim::graph::FmuNode*>();

    for (int i = 0; i < ssp.resources.size(); i++)
    {
        auto resource = ssp.resources[i];
        // TODO: Check that the resource is a fmu...
        auto fmu = ssp4cpp::Fmu(ssp.resources[i].file);
        auto name = resource.name.value_or("null");
        auto fmu_node = new sim::graph::FmuNode(name);

        // fmu_node.fmu = fmu;

        fmus[name] = fmu_node;
    }

    log.debug("Map {}", common::str::to_str(fmus));

    for (auto const [key, value] : fmus)
    {
        log.debug("{} : {}", key, value->to_str());
    }


    auto fmu_connections = set<pair<string, string>>();

    for (auto connection : ssp.ssd.System.Connections.value().Connections)
    {
        auto p = std::make_pair(connection.startElement.value(), connection.endElement.value());
        fmu_connections.insert(p);

        // auto start = connection.startElement.value() + "." + connection.startConnector;
        // auto end = connection.endElement.value() + "." + connection.endConnector;

        // cout << start << ": " << connector_str_int_map[start] << " -> " << end << ": " << connector_str_int_map[end] << endl;
    }

    for (auto p : fmu_connections)
    {
        log.debug("Connection: {} -> {}", p.first, p.second);
    }

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
