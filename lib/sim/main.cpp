

#include "ssp.hpp"
#include "fmu.hpp"
#include "common_io.hpp"
#include "common_log.hpp"

#include "SSP1_SystemStructureDescription_Ext.hpp"
#include "FMI2_modelDescription_Ext.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <iostream>
#include <fstream>
#include <cassert>

#include <vector>
#include <algorithm>
#include <map>
#include <list>

using namespace std;
using namespace fmi4cpp;
using namespace ssp4cpp;
using namespace common::io;
using namespace common;

// class Connection
// {
//     fmu source_fmu;
//     connector source_connector;

//     fmu traget_fmu;
//     connector target_connector;

//     Connection() {}

// };

int main()
{
    auto log = Logger("cosim.main", LogLevel::debug);
    log.debug("Opening ssp");

    auto ssp = ssp4cpp::Ssp("./resources/algebraic_loop_4.ssp");

    log.debug("Imported ssp! \n");
    log.debug("{}", ssp.to_str());

    // Parsing FMI
    auto fmus = vector<pair<string, ssp4cpp::Fmu>>();
    auto fmu_name_to_ssp_name = pair<string, string>();

    for (int i = 0; i < ssp.resources.size(); i++)
    {
        auto resource = ssp.resources[i];

        auto fmu = ssp4cpp::Fmu(ssp.resources[i].file);
        auto p = pair(resource.name.value_or("null"), fmu);
        fmus.push_back(p);
    }

    // Count nodes
    map<string, int> connector_str_int_map;

    ssp4cpp::ssp1::ssd::IndexConnectorComponentTuples connectors;

    if (ssp.ssd.System.Elements.has_value())
    {
        connectors = ssp1::ssd::Elements_Ext::get_connectors(
            ssp.ssd.System.Elements.value(),
            {ssp4cpp::fmi2::md::Causality::input, ssp4cpp::fmi2::md::Causality::output});

        for (auto [index, connector, component] : connectors)
        {
            auto name = component.get().name.value() + "." + connector.get().name;
            connector_str_int_map[name] = index;
        }
    }

    cout << common::str::to_str(connector_str_int_map);

    std::cout << "add ssp edges\n";
    for (auto connection : ssp.ssd.System.Connections.value().Connections)
    {
        auto start = connection.startElement.value() + "." + connection.startConnector;
        auto end = connection.endElement.value() + "." + connection.endConnector;

        cout << start << ": " << connector_str_int_map[start] << " -> " << end << ": " << connector_str_int_map[end] << endl;
    }

    std::cout << "Parsing complete\n";
}