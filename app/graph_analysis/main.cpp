

#include "ssp.hpp"
#include "fmu.hpp"

#include "dsm.hpp"

#include "SSP1_SystemStructureDescription_Ext.hpp"
#include "FMI2_modelDescription_Ext.hpp"

#include <iostream>
#include <fstream>
#include <cassert>

#include <boost/config.hpp>
#include <vector>
#include <algorithm> // std::unique, std::distance
#include <list>

// #include <boost/graph/strong_components.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

#include <fmi4cpp/fmi4cpp.hpp>


using namespace std;
using namespace boost;
using namespace fmi4cpp;
using namespace ssp4cpp;
using namespace ssp4cpp::common;


int main()
{
    auto log = Logger("graph_analysis.main", LogLevel::debug);
    
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

    dsm::Graph g;
    ssp4cpp::ssp1::ssd::IndexConnectorComponentTuples connectors;

    if (ssp.ssd.System.Elements.has_value())
    {
        connectors = ssp1::ssd::Elements_Ext::get_connectors(
            ssp.ssd.System.Elements.value(),
            {ssp4cpp::fmi2::md::Causality::input, ssp4cpp::fmi2::md::Causality::output});

        g = dsm::Graph(connectors.size());

        for (auto [index, connector, component] : connectors)
        {
            auto name = component.get().name.value() + "." + connector.get().name;

            connector_str_int_map[name] = index;
            // cout << index << " : " << connector.get().name << endl;

            g[index].name = name;
            g[index].component = component.get().name.value();
            g[index].connector = connector.get().name;
        }
    }


    std::cout << "add ssp edges\n";
    for (auto connection : ssp.ssd.System.Connections.value().Connections)
    {
        auto start = connection.startElement.value() + "." + connection.startConnector;
        auto end = connection.endElement.value() + "." + connection.endConnector;

        add_edge(connector_str_int_map[start], connector_str_int_map[end], g);
        // cout << start << ": " << connector_str_int_map[start] << " -> " << end << ": " << connector_str_int_map[end] << endl;
    }

    std::cout << "add fmu edges\n";
    for (auto [name, fmu] : fmus)
    {
        // std::cout << fmu.md.modelName << endl;
        auto outputs = fmu.md.ModelStructure.Outputs;
        if (!outputs.has_value())
        {
            std::cout << fmu.md.modelName << " No outputs" << endl;
            continue;
        }

        auto dependencies = ssp4cpp::fmi2::md::Unknown_Ext::get_dependencies_variables(
            outputs.value().Unknowns,
            fmu.md.ModelVariables,
            ssp4cpp::fmi2::md::DependenciesKind::dependent);

        for (auto &[output, input, kind] : dependencies)
        {
            auto input_name = name + "." + input.name;
            auto output_name = name + "." + output.name;

            if (input.causality == ssp4cpp::fmi2::md::Causality::input)
            {
                // std::cout << "Input: " << input_name << " " << connector_str_int_map[input_name] << " -> " << "Output: " << output_name << " " << connector_str_int_map[output_name] << endl;
                add_edge(connector_str_int_map[input_name], connector_str_int_map[output_name], g);
            }
            else
            {
                // std::cout << "Dependency: " << input_name << " -> " << "Causality: " << to_str(input.causality) << endl;
            }
        }
    }

    // boost::write_graphviz(std::cout, g, make_label_writer(get(&dsm::vertex_info::name, g)));

    // add_edge(connector_str_int_map["dynamic_connection_fmu_fmu1.dynamic_input_1"], connector_str_int_map["dynamic_connection_fmu_fmu1.dynamic_output_1"], g);
    // add_edge(connector_str_int_map["dynamic_connection_fmu_fmu1.dynamic_input_2"], connector_str_int_map["dynamic_connection_fmu_fmu1.dynamic_output_2"], g);
    // add_edge(connector_str_int_map["dynamic_connection_fmu_fmu2.dynamic_input_1"], connector_str_int_map["dynamic_connection_fmu_fmu2.dynamic_output_1"], g);
    // add_edge(connector_str_int_map["dynamic_connection_fmu_fmu2.dynamic_input_2"], connector_str_int_map["dynamic_connection_fmu_fmu2.dynamic_output_2"], g);
    // add_edge(connector_str_int_map["dynamic_connection_fmu_fmu3.dynamic_input_1"], connector_str_int_map["dynamic_connection_fmu_fmu3.dynamic_output_1"], g);
    // add_edge(connector_str_int_map["dynamic_connection_fmu_fmu3.dynamic_input_2"], connector_str_int_map["dynamic_connection_fmu_fmu3.dynamic_output_2"], g);
    // add_edge(connector_str_int_map["dynamic_connection_fmu_fmu4.dynamic_input_1"], connector_str_int_map["dynamic_connection_fmu_fmu4.dynamic_output_1"], g);
    // add_edge(connector_str_int_map["dynamic_connection_fmu_fmu4.dynamic_input_2"], connector_str_int_map["dynamic_connection_fmu_fmu4.dynamic_output_2"], g);


    ssp4cpp::dsm::DSM dsm(g);

    cout <<  dsm.GetCSV();
    // dsm.PrintGroups();


    std::cout << "Parsing complete\n";
}