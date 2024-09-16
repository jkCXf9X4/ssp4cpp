
#include <iostream>
#include <fstream>
#include <cassert>

#include "ssp_import.hpp"

#include <boost/config.hpp>
#include <vector>
#include <iostream>
#include <algorithm> // std::unique, std::distance

// #include <boost/graph/strong_components.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "fmi4c.h"

#include <list>

using namespace std;
using namespace boost;

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
    auto fmus = vector<fmiHandle*>();

    for (int i = 0; i < ssp.resources.size(); i++)
    {   
        auto r = ssp.resources[i];
        auto fmu = fmi4c_loadFmu(r.file.c_str(), r.name.value().c_str());

        if (!fmu)
        {
            printf("Failed to load FMU\n");
            exit(1);
        }
        cout << "Creating FMU " << i << " : " << r.name.value_or("null") << endl;
        cout << "Version " << fmi4c_getFmiVersion(fmu) << endl;

        fmus.push_back(fmu);
    }

    for (auto fmu : fmus)
    {
        cout << fmi2_getModelName(fmu) << endl;
        // cout << fmi2_getNumberOfModelStructureOutputs(fmu) << endl;
        // fmi4c_freeFmu(fmu);
    }
    return 0;

    
    map<string, int> connector_map;
    {
        int connector_index = 0;
        // index all connectors
        for (auto component : ssp.ssd.System.Elements.value().components)
        {
            // cout << component  << endl;
            for (auto connector : component.Connectors.value().list)
            {
                if (connector.kind == "input" || connector.kind == "output")
                {
                    auto name = component.name.value() + "." + connector.name;
                    connector_map[name] = connector_index++;
                    // cout << name << endl;
                }
            }
        }
    }

    typedef adjacency_list<vecS, vecS, boost::directedS, property< vertex_name_t, std::string >> Graph;
    // typedef std::pair<int, int> Edge;

    cout << "Connectors: " << connector_map.size() << endl;
    Graph g(connector_map.size());

    for (auto [name, index] : connector_map)
    {
        boost::put(boost::vertex_name_t(), g, index, name);
    }

    for (auto connection : ssp.ssd.System.Connections.value().list)
    {
        auto start = connection.startElement.value() + "." + connection.startConnector;
        auto end = connection.endElement.value() + "." + connection.endConnector;

        add_edge(connector_map[start], connector_map[end], g);
        // cout << connector_map[start] << " -> " << connector_map[end] << endl;
    }

    boost::write_graphviz(std::cout, g, make_label_writer(get(boost::vertex_name_t(), g)));




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