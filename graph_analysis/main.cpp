
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

#include <list>

using namespace std;

int main()
{
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);

    // Opening zip
    cout << "Opening ssp\n";

    auto ssp = ssp4cpp::ssp1::SspImport("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/graph_analysis/resources/embrace.ssp");

    cout << ssp << endl;

    ofstream myfile;
    myfile.open("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/graph_analysis/resources/parsed.txt");
    myfile << ssp.ssd;
    myfile.close();

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