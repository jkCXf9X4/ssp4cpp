

#include "ssp_import.hpp"
#include "fmi_import.hpp"
#include "common_io.hpp"
#include "common_log.hpp"


#include "SSP1_SystemStructureDescription_Ext.hpp"
#include "FMI2_modelDescription_Ext.hpp"

#include <iostream>
#include <fstream>
#include <cassert>

#include <boost/config.hpp>
#include <vector>
#include <algorithm> 

#include <list>

#include <fmi4cpp/fmi4cpp.hpp>
#include <map>

using namespace std;
using namespace boost;
using namespace fmi4cpp;
using namespace ssp4cpp;
using namespace common::io;
using namespace common;

int main()
{
    auto log = Logger("cosim.main", LogLevel::debug);

    // Opening zip
    std::cout << "Opening ssp\n";

    auto ssp = ssp4cpp::ssp1::SspImport("./resources/algebraic_loop_4.ssp");

    std::cout << "Imported ssp! \n";

    std::cout << ssp << endl;

    std::cout << "Parsing ssp to external file\n";

    save_string("./resources/parsed.txt", ssp.ssd.to_string());

    // Parsing FMI
    auto fmus = vector<pair<string, ssp4cpp::fmi2::FmiImport>>();
    auto fmu_name_to_ssp_name = pair<string, string>();

    for (int i = 0; i < ssp.resources.size(); i++)
    {
        auto resource = ssp.resources[i];

        auto fmu = ssp4cpp::fmi2::FmiImport(ssp.resources[i].file);
        auto p = pair(resource.name.value_or("null"), fmu);
        fmus.push_back(p);

        save_string("./" + std::to_string(i) + ".txt", fmu.md.to_string());
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