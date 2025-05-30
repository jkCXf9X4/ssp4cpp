#include "ssp.hpp"
#include "fmu.hpp"
#include "ssp_ext.hpp"
#include "common_io.hpp"
#include "common_log.hpp"
#include "common_string.hpp"
#include "common_node.hpp"
#include "common_json.hpp"
#include "common_node.hpp"
#include "common_map.hpp"
#include "tarjan.hpp"

#include "SSP1_SystemStructureDescription_Ext.hpp"
#include "FMI2_modelDescription_Ext.hpp"

#include "connection.hpp"
#include "system_graph.hpp"

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

class Simulator
{
public:
    common::Logger log = Logger("Simulator", LogLevel::debug);

    unique_ptr<Ssp> ssp;
    map<string, unique_ptr<Fmu>> fmu_map; // owner
    map<string, Fmu*> fmu_map_ref;

    common::json::Json model_props;

    // system_graph: Simple graph only showing the connections between fmu's
    vector<common::graph::Node *> system_graph;
    vector<vector<common::graph::Node *>> strong_system_graph;

    Simulator(const string &ssp_path,
              const string &props_path)
    {
        ssp = make_unique<ssp4cpp::Ssp>(ssp_path);
        log.debug("SSP: {}", ssp->to_string());

        model_props = json::parse_json_file(props_path);
        log.debug("Extra properties:\n{}\n", json::to_string(model_props));

        fmu_map = ssp4cpp::ssp::ext::create_fmu_map(*ssp);
        fmu_map_ref = map_ns::map_unique_to_ref(fmu_map);

        // system graph
        system_graph = ssp4cpp::sim::graph::create_system_graph(*ssp, fmu_map_ref);
        log.info("System graph DOT \n{}", graph::Node::to_dot(system_graph));
        
        strong_system_graph = graph::strongly_connected_components(system_graph);
        log.info("{}", graph::ssc_to_string(strong_system_graph));
        
        // create connection graph
        
        auto connection_graph = ssp4cpp::sim::graph::create_connection_graph(*ssp, fmu_map_ref);
        log.info("Connections graph DOT \n{}", graph::Node::to_dot(connection_graph));

        auto strong_connection_graph = graph::strongly_connected_components(connection_graph);
        log.info("{}", graph::ssc_to_string(strong_connection_graph));

        // create all models

        // create all connectors




    }

    ~Simulator()
    {
        // unique_ptr will automatically clean up FMUs and SSP
        // when this is destroyed the application will end, no need to free memory resources
    }

    void execute()
    {
        log.info("Executing simulation...");

        for (auto node : system_graph)
        {
            log.debug("Executing node: {}", node->name);
        }

        log.info("Simulation execution complete.");
    }
};

int main()
{
    auto log = Logger("main", LogLevel::debug);

    auto sim = Simulator("./resources/algebraic_loop_4.ssp", "./resources/model_props.json");

    sim.execute();

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
