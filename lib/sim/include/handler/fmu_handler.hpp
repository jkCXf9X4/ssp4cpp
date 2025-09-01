#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "ssp.hpp"
#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::handler
{
    using namespace std;

    struct FmuInfo
    {
        std::string system_name;
        std::string model_name;

        // Borrowing
        ssp4cpp::Fmu *fmu;
        ssp4cpp::fmi2::md::fmi2ModelDescription*  model_description;

        // Owning
        std::unique_ptr<fmi4cpp::fmi2::fmu> fmi4cpp_fmu;
        std::unique_ptr<fmi4cpp::fmi2::cs_fmu> cs_fmu;
        std::unique_ptr<fmi4cpp::fmi2::cs_slave> model;


        FmuInfo(std::string name, ssp4cpp::Fmu *fmu)
        {
            this->model_name = fmu->md->modelName;
            this->system_name = name;

            this->fmu = fmu;

            this->fmi4cpp_fmu = make_unique<fmi4cpp::fmi2::fmu>(this->fmu->original_file);
            this->cs_fmu = this->fmi4cpp_fmu->as_cs_fmu();

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

        map<string, std::unique_ptr<FmuInfo>> fmu_info_map;

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
            fmu_ref_map = map_ns::map_unique_to_ref(fmu_map);
            
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
                fmu->model = fmu->cs_fmu->new_instance();
            }
            log.trace("[{}] Model init completed", __func__);
        }
    };

}