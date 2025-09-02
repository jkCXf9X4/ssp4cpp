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
    class Simulator
    {
    public:
        common::Logger log = common::Logger("Simulator", common::LogLevel::info);

        std::unique_ptr<Ssp> ssp;
        std::unique_ptr<Simulation> sim;

        Simulator(const std::string &ssp_path,
                  const std::string &props_path)
        {
            log.info("[{}] Creating Simulator\n", __func__);
            log.debug("[{}] - Importing SSP", __func__);
            ssp = std::make_unique<ssp4cpp::Ssp>(ssp_path);
            log.debug("[{}] -- SSP: {}", __func__, ssp->to_string());
            
            log.debug("[{}] - Loading config", __func__);
            utils::Config::loadFromFile(props_path);
            log.debug("[{}] -- Config:\n{}\n", __func__, utils::Config::as_string());
            
            log.debug("[{}] - Creating simulation\n", __func__);
            sim = std::make_unique<Simulation>(ssp.get());
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
