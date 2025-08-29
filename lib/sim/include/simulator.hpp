#include "ssp.hpp"
#include "fmu.hpp"
#include "common_io.hpp"
#include "common_log.hpp"
#include "common_json.hpp"
#include "common_map.hpp"

#include "simulation.hpp"
#include "config.hpp"

#include <vector>
#include <map>

namespace ssp4cpp::sim
{
    
    using namespace std;
    using namespace ssp4cpp;
    using namespace common::io;
    using namespace common;

    class Simulator
    {
    public:
        common::Logger log = Logger("Simulator", LogLevel::info);

        std::unique_ptr<Ssp> ssp;
        std::map<std::string, std::unique_ptr<Fmu>> fmus;
        std::map<std::string, ssp4cpp::Fmu *> fmus_ref; // Non owning

        // system_graph: Simple graph only showing the connections between fmu's
        std::unique_ptr<Simulation> sim;

        Simulator(const string &ssp_path,
                  const string &props_path)
        {
            log.info("[{}] Creating Simulator\n", __func__);
            log.debug("[{}] Importing SSP", __func__);
            ssp = make_unique<ssp4cpp::Ssp>(ssp_path);
            log.debug("[{}] SSP: {}", __func__, ssp->to_string());
            
            log.debug("[{}] Creating FMU map", __func__);
            fmus = ssp4cpp::ssp::ext::create_fmu_map(*ssp);
            for (auto &[fmu_name, fmu] : fmus)
            {
                log.debug("[{}] FMU: {} - ", __func__, fmu_name, fmu->to_string());
            }

            fmus_ref = map_ns::map_unique_to_ref(fmus);

            utils::Config::loadFromFile(props_path);
            log.debug("[{}] Config:\n{}\n", __func__, utils::Config::as_string());
            
            log.debug("[{}] Creating simulation\n", __func__);
            sim = make_unique<Simulation>(ssp.get(), fmus_ref);
        }
        
        ~Simulator()
        {
            // std::unique_ptr will automatically clean up FMUs and SSP
            // when this is destroyed the application will end, no need to free memory resources
        }
        
        void init()
        {
            log.info("[{}] Initializing Simulator\n", __func__);
            sim->init();
        }
        
        void simulate()
        {
            log.info("[{}] Starting Simulator\n", __func__);
            sim->simulate();
        }


    };
}
