
#include <iostream>
#include <fstream>

#include "ssp_import.hpp"

#include <boost/config.hpp>
#include <vector>
#include <iostream>
// #include <boost/graph/strong_components.hpp>
// #include <boost/graph/adjacency_list.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "fmi4c.h"

#include <list>

using namespace std;

int main()
{
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);

    // Opening zip
    cout << "Opening ssp\n";

    auto ssp = ssp4cpp::ssp1::SspImport("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/graph_analysis/resources/embrace.ssp");

    cout << "Imported ssp\n";

    cout << ssp << endl;

    cout << "Parsing ssp to external file\n";

    ofstream myfile;
    myfile.open("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/graph_analysis/resources/parsed.txt");
    myfile << ssp.ssd;
    myfile.close();

    // Parsing FMI

    auto fmu_path = ssp.resources[0].file.c_str();

    fmiHandle *fmu = fmi4c_loadFmu(fmu_path, "myfmu");
    cout << "Version " << fmi4c_getFmiVersion(fmu);

    if(!fmu) {
        printf("Failed to load FMU\n");
        exit(1);
    }

    auto connectors = list<string>();

    //     startElement: AdaptionUnit
    // startConnector: sWsignals.TLiquid
    // endElement: ECS_SW
    // endConnector: Input.TLiquid

    // for (auto connection : ssp.ssd.System.Connections.value().list)
    // {
    //     cout << connection.startElement.value().append(connection.startConnector) << endl;
    // }

    cout << "Parsing complete\n";
}