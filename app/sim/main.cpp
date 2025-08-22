// #include "ssp.hpp"
// #include "fmu.hpp"
// #include "ssp_ext.hpp"
// #include "common_io.hpp"
#include "common_log.hpp"
// #include "common_string.hpp"
// #include "common_node.hpp"
// #include "common_json.hpp"
// #include "common_node.hpp"
// #include "common_map.hpp"
// #include "common_thread_pool.hpp"
// #include "common_time.hpp"

// #include "tarjan.hpp"

// #include "SSP1_SystemStructureDescription_Ext.hpp"
// #include "FMI2_modelDescription_Ext.hpp"

#include "simulator.hpp"

// #include <unordered_set>
// #include <iostream>
// #include <fstream>
// #include <cassert>
// #include <vector>
// #include <algorithm>
// #include <map>
// #include <set>
// #include <list>

using namespace ssp4cpp;
using namespace ssp4cpp::common;

int main()
{
    auto log = Logger("main", LogLevel::debug);
    log.ext_trace("[{}] enter", __func__);

    // auto sim = Simulator("./resources/algebraic_loop_4.ssp", "./resources/model_props.json");
    // auto sim = sim::Simulator("./resources/delay_sys.ssp", "./resources/model_props.json");
    auto sim = sim::Simulator("./resources/embrace.ssp", "./resources/model_props.json");
    sim.init();
    sim.simulate();

    log.ext_trace("[{}] exit", __func__);
    return 0;
}
