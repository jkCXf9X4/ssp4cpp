#include "ssp.hpp"
#include "fmu.hpp"
#include "common_io.hpp"
#include "common_log.hpp"
#include "common_json.hpp"
#include "common_map.hpp"

#include "simulation.hpp"

#include <vector>
#include <map>

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
        std::map<std::string, std::unique_ptr<Fmu>> fmus;
        std::map<std::string, ssp4cpp::Fmu *> fmus_ref; // Non owning

        common::json::Json model_props;

        // system_graph: Simple graph only showing the connections between fmu's
        unique_ptr<Simulation> sim;

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

            sim = make_unique<Simulation>(ssp.get(), fmus_ref);
        }

        ~Simulator()
        {
            // unique_ptr will automatically clean up FMUs and SSP
            // when this is destroyed the application will end, no need to free memory resources
        }

        void init()
        {
            sim->init();
        }

        void simulate()
        {
            sim->simulate();
        }


    };
}
