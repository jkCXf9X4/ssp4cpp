#include "ssp.hpp"
#include "fmu.hpp"
// #include "ssp_ext.hpp"
#include "common_io.hpp"
#include "common_log.hpp"
// #include "common_string.hpp"
// #include "common_node.hpp"
#include "common_json.hpp"
// #include "common_node.hpp"
#include "common_map.hpp"
// #include "common_thread_pool.hpp"
// #include "common_time.hpp"
// #include <unordered_set>


// #include "SSP1_SystemStructureDescription_Ext.hpp"
// #include "FMI2_modelDescription_Ext.hpp"

#include "simulation.hpp"

// #include <iostream>
// #include <fstream>
// #include <cassert>
#include <vector>
// #include <algorithm>
#include <map>
// #include <set>
// #include <list>

using namespace std;
using namespace ssp4cpp;
using namespace common::io;
using namespace common;

namespace ssp4cpp::sim
{

    class Simulator
    {
    public:
        common::Logger log = Logger("Simulator", LogLevel::info);

        unique_ptr<Ssp> ssp;
        std::map<std::string, std::unique_ptr<ssp4cpp::Fmu>> fmus;
        std::map<std::string, ssp4cpp::Fmu *> fmus_ref; // Non owning

        common::json::Json model_props;

        // system_graph: Simple graph only showing the connections between fmu's
        Simulation sim;

        Simulator(const string &ssp_path,
                  const string &props_path)
        {
            ssp = make_unique<ssp4cpp::Ssp>(ssp_path);
            log.debug("[{}] SSP: {}", __func__, ssp->to_string());

            fmus = ssp4cpp::ssp::ext::create_fmu_map(*ssp);
            for (auto &[fmu_name, fmu] : fmus)
            {
                log.debug("[{}] FMU: {} - ", __func__, fmu_name, fmu->to_string());
            }

            fmus_ref = map_ns::map_unique_to_ref(fmus);

            model_props = json::parse_json_file(props_path);
            log.debug("[{}] Extra properties:\n{}\n", __func__, json::to_string(model_props));

            sim = Simulation(ssp.get(), fmus_ref);
            sim.init();

            sim.execute();
        }

        ~Simulator()
        {
            // unique_ptr will automatically clean up FMUs and SSP
            // when this is destroyed the application will end, no need to free memory resources
        }


    };
}
