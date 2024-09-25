
#include <iostream>
#include <fstream>
#include <cassert>

#include "ssp_import.hpp"
#include "fmi_import.hpp"

#include <boost/config.hpp>
#include <vector>
#include <algorithm> // std::unique, std::distance

// #include <boost/graph/strong_components.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "SystemStructureDescription.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <list>

using namespace std;
using namespace boost;
using namespace fmi4cpp;

void save_string(const string &filename, const string &content)
{
    ofstream myfile;
    myfile.open(filename);
    myfile << content;
    myfile.close();
}

int main()
{
    boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);

    // Opening zip
    std::cout << "Opening ssp\n";

    auto ssp = ssp4cpp::ssp1::SspImport("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/graph_analysis/resources/embrace.ssp");

    std::cout << "Imported ssp! \n";

    std::cout << ssp << endl;

    std::cout << "Parsing ssp to external file\n";

    save_string("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/graph_analysis/resources/parsed.txt", ssp.ssd.to_string());

    // Parsing FMI
    auto fmus = vector<ssp4cpp::fmi2::FmiImport>();

    auto fmu_name_to_ssp_name = map<string, string>();

    for (int i = 0; i < ssp.resources.size(); i++)
    {

        auto fmu = ssp4cpp::fmi2::FmiImport(ssp.resources[i].file);
        fmus.push_back(fmu);

        save_string("/home/eriro/pwa/2_work/loop/repos/ssp4cpp/test/graph_analysis/resources/" + std::to_string(i) + ".txt", fmu.md.to_string());

        auto resource = ssp.resources[i];
        fmu_name_to_ssp_name[fmu.md.modelName] = resource.name.value_or("null");
    }

    for (auto const &x : fmu_name_to_ssp_name)
    {
        std::cout << x.first // string (key)
                  << ':'
                  << x.second // string's value
                  << std::endl;
    }

    for (auto fmu : fmus)
    {
        std::cout << fmu.md.modelName << endl;
        auto outputs = fmu.md.ModelStructure.Outputs;
        if (!outputs.has_value())
        {
            std::cout << "No outputs" << endl;
            continue;
        }

        for (ssp4cpp::fmi2::Unknown output : outputs.value().Unknowns)
        {
            std::cout << "Index: " << output.index << endl;
            if (!output.dependencies.has_value())
            {
                std::cout << "No dependencies" << endl;
                continue;
            }
            for (int i = 0; i < output.dependencies.value().list.size(); i++)
            {
                auto dependency = output.dependencies.value().list[i];
                auto dependency_kind = output.dependenciesKind.value().list[i];

                if (dependency_kind == ssp4cpp::fmi2::DependenciesKind::Value::dependent)
                {
                    std::cout << "Dependent: " << output.index << " : " << dependency << endl;
                }
            }
        }
    }

    return 0;

    map<string, int> connector_map;
    {
        int connector_index = 0;
        // index all connectors
        for (auto component : ssp.ssd.System.Elements.value().Components)
        {
            // cout << component  << endl;
            for (auto connector : component.Connectors.value().Connectors)
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

    std::cout << "Connectors: " << connector_map.size() << endl;
    Graph g(connector_map.size());

    for (auto [name, index] : connector_map)
    {
        boost::put(boost::vertex_name_t(), g, index, name);
    }

    for (auto connection : ssp.ssd.System.Connections.value().Connections)
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

    std::cout << "Parsing complete\n";
}