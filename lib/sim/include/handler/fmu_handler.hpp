#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "ssp.hpp"
#include "fmu.hpp"

#include "fmi4c_adapter.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>
#include <format>

namespace ssp4cpp::sim::handler
{
    // using namespace std;

    struct FmuInfo
    {
        std::string system_name;
        std::string model_name;

        // Borrowing
        ssp4cpp::Fmu *fmu;
        ssp4cpp::fmi2::md::fmi2ModelDescription *model_description;

        // Owning
        std::unique_ptr<FmuInstance> fmi_instance;
        std::unique_ptr<CoSimulationModel> model;

        FmuInfo(std::string name, ssp4cpp::Fmu *fmu)
        {
            this->model_name = fmu->md->modelName;
            this->system_name = name;

            this->fmu = fmu;

            this->fmi_instance = std::make_unique<FmuInstance>(this->fmu->original_file, this->system_name);
            if (!this->fmi_instance->supports_co_simulation())
            {
                throw std::runtime_error(std::format("FMU '{}' does not support co-simulation", this->system_name));
            }
            this->model = std::make_unique<CoSimulationModel>(*this->fmi_instance);

            this->model_description = fmu->md.get();
        }
        // can not be copied, has unique pointers
        FmuInfo(const FmuInfo &) = delete;
        FmuInfo &operator=(const FmuInfo &) = delete;
    };

    class FmuHandler
    {
    public:
        common::Logger log = common::Logger("FmuHandler", common::LogLevel::debug);

        Ssp *ssp;

        std::map<std::string, std::unique_ptr<Fmu>> fmu_map;
        std::map<std::string, ssp4cpp::Fmu *> fmu_ref_map; // Non owning

        std::map<std::string, std::unique_ptr<FmuInfo>> fmu_info_map;

        FmuHandler(ssp4cpp::Ssp *ssp)
        {
            this->ssp = ssp;

            log.debug("[{}] Creating FMU map", __func__);
            fmu_map = ssp4cpp::ssp::ext::create_fmu_map(*ssp);
            for (auto &[fmu_name, fmu] : fmu_map)
            {
                log.debug("[{}] - FMU: {} - ", __func__, fmu_name, fmu->to_string());
            }

            // create a non owning variant to be passed around
            fmu_ref_map = common::map_ns::map_unique_to_ref(fmu_map);

            log.debug("[{}] Creating FMU Info map", __func__);
            for (auto &[name, fmu] : fmu_ref_map)
            {
                fmu_info_map.emplace(name, make_unique<FmuInfo>(name, fmu));
            }
        }

        void init()
        {
            log.trace("[{}] Model init ", __func__);
            for (auto &[_, fmu] : this->fmu_info_map)
            {
                fmu->model->instantiate(false, false);
            }
            log.trace("[{}] Model init completed", __func__);
        }
    };
}
