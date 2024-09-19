
#include <iostream>
#include <fstream>
#include <cassert>

#include "ssp_import.hpp"
#include "fmi_import.hpp"

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

#include <fmi4cpp/fmi4cpp.hpp>

#include <list>

using namespace std;
using namespace boost;
using namespace fmi4cpp;

int main()
{
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);

    // Opening zip
    cout << "Opening ssp\n";

    auto ssp = ssp4cpp::ssp1::SspImport("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/graph_analysis/resources/embrace.ssp");

    cout << "Imported ssp! \n";

    cout << ssp << endl;

    cout << "Parsing ssp to external file\n";

    ofstream myfile;
    myfile.open("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/graph_analysis/resources/parsed.txt");
    myfile << ssp.ssd.to_string();
    myfile.close();

    return 0;

    // Parsing FMI
    auto fmus = vector<fmi2::fmu>();

    auto fmu_name_to_ssp_name = map<string, string>();

    for (int i = 0; i < ssp.resources.size(); i++)
    {

        // auto fmi = ssp4cpp::fmi2::FmiImport(ssp.resources[i].file);
        // cout << fmi.md.to_string() << endl;

        return 0;


        auto resource = ssp.resources[i];
        auto fmu = fmi2::fmu(resource.file.c_str());

        // auto cs_fmu = fmu.as_cs_fmu();

        cout << "Creating FMU " << i << " : " << resource.name.value_or("null") << endl;
        cout << "Creating FMU " << i << " : " << fmu.model_name() << endl;

        fmu_name_to_ssp_name[fmu.model_name()] = resource.name.value_or("null");
        // auto cs_md = cs_fmu->get_model_description(); //smart pointer to a cs_model_description instance
        // std::cout << "model_identifier=" << cs_md->model_identifier << std::endl;

        fmus.push_back(fmu);
    }

    for (auto fmu : fmus)
    {
        cout << fmu.model_name() << endl;
        auto md = fmu.get_model_description();
        for (auto output : md->model_structure->outputs)
        {
            cout << "Index: " << output.index << endl;
            if (output.dependencies.has_value())
            {
                for (int i = 0; i < output.dependencies.value().size(); i++)
                {
                    // cout << i << " : " << output.dependencies.value()[i] << endl;
                    cout << output.dependencies.value()[i] << " : " << output.dependencies_kind.value()[i] << endl;
                    if (output.dependencies_kind.value()[i] == "dependent")
                    {
                        cout << "Dependent" << endl;
                    }
                    else
                    {
                        cout << "Independent" << endl;
                    }
                }   
            }
        }
        // cout << fmi2_getNumberOfModelStructureOutputs(fmu) << endl;
        // fmi4c_freeFmu(fmu);
    }
    // return 0;

    map<string, int> connector_map;
    {
        int connector_index = 0;
        // index all connectors
        for (auto component : ssp.ssd.System.Elements.value().Component)
        {
            // cout << component  << endl;
            for (auto connector : component.Connectors.value().Connector)
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

    typedef adjacency_list<vecS, vecS, boost::directedS, property<vertex_name_t, std::string>> Graph;
    // typedef std::pair<int, int> Edge;

    cout << "Connectors: " << connector_map.size() << endl;
    Graph g(connector_map.size());

    for (auto [name, index] : connector_map)
    {
        boost::put(boost::vertex_name_t(), g, index, name);
    }

    for (auto connection : ssp.ssd.System.Connections.value().Connection)
    {
        auto start = connection.startElement.value() + "." + connection.startConnector;
        auto end = connection.endElement.value() + "." + connection.endConnector;

        add_edge(connector_map[start], connector_map[end], g);
        // cout << connector_map[start] << " -> " << connector_map[end] << endl;
    }

    // boost::write_graphviz(std::cout, g, make_label_writer(get(boost::vertex_name_t(), g)));

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