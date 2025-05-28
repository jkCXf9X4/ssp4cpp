

#include "ssp.hpp"
#include "fmu.hpp"
#include "ssp_ext.hpp"
#include "common_io.hpp"
#include "common_log.hpp"
#include "common_string.hpp"
#include "common_node.hpp"
#include "common_json.hpp"
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


int main()
{
    auto log = Logger("sim.main", LogLevel::debug);
    log.debug("Opening SSP");

    auto ssp = ssp4cpp::Ssp("./resources/algebraic_loop_4.ssp");
    log.debug("SSP: {}", ssp.to_string());

    auto delays = json::parse_json_file("./resources/model_props.json");
    log.debug("Extra properties:\n{}\n", json::to_string(delays));

    auto system_nodes = ssp4cpp::sim::graph::create_system_graph(ssp);

    log.info("DOT \n{}", common::graph::Node::to_dot_s(system_nodes));

    auto ssc = common::graph::strongly_connected_components(system_nodes);
    log.info("{}", common::graph::ssc_to_string(ssc));





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
