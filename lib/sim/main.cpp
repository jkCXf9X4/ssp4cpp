

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
    // log.debug("ssp: {}", ssp.to_string());

    auto fmus = map<string, ssp4cpp::Fmu>();
    for( auto &resource: ssp4cpp::ssp1::ext::ssd::get_resources(ssp.ssd))
    {
        auto r = *resource;
        auto name = r.name.value_or("null");
        auto source = r.source;
        auto path = ssp.temp_dir / r.source;
        log.debug("Importing {} {} {}", name, source, path.string());
        auto fmu = ssp4cpp::Fmu(path);
        // auto fmu_node = new sim::graph::FmuNode(name);
        
        fmus[name] = fmu;
    }


    // log.debug("Map {}", common::str::to_str(fmus));

    // for (auto const& [key, value] : fmus)
    // {
        // log.debug("{} : {}", key, "");
    // }



    // auto fmu_connections = set<pair<string, string>>();

    // for (auto connection : ssp.ssd.System.Connections.value().Connections)
    // {
    //     auto p = std::make_pair(connection.startElement.value(), connection.endElement.value());
    //     fmu_connections.insert(p);

    //     // auto start = connection.startElement.value() + "." + connection.startConnector;
    //     // auto end = connection.endElement.value() + "." + connection.endConnector;

    //     // cout << start << ": " << connector_str_int_map[start] << " -> " << end << ": " << connector_str_int_map[end] << endl;
    // }

    // for (auto p : fmu_connections)
    // {
    //     log.debug("Connection: {} -> {}", p.first, p.second);
    // }

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
