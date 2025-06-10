#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

#include "ssp_ext.hpp"

#include <fmi4cpp/fmi4cpp.hpp>

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::sim::handler
{
    using namespace std;

    class FmuHandler
    {
    public:
        common::Logger log = common::Logger("sim::FmuHandler", common::LogLevel::ext_trace);

        struct fmu_info
        {
            ssp4cpp::Fmu *fmu;
            unique_ptr<fmi4cpp::fmi2::cs_fmu> cs_fmu;
            unique_ptr<fmi4cpp::fmi2::cs_slave> model;
            std::shared_ptr<const fmi4cpp::fmi2::cs_model_description> model_description;
        };

        map<string, fmu_info> fmus;

        FmuHandler(std::map<std::string, ssp4cpp::Fmu *> &str_fmu)
        {
            for (auto &[name, fmu] : str_fmu)
            {
                fmu_info f;
                f.fmu = fmu;
                auto fmu_t = fmi4cpp::fmi2::fmu(fmu->original_file);
                f.cs_fmu = fmu_t.as_cs_fmu();
                f.model_description = f.cs_fmu->get_model_description();

                fmus[name] = std::move(f);
            }
        }

        void init()
        {
            log.trace("[{}] Model init ", __func__);
            for (auto &[_, fmu] : this->fmus)
            {
                fmu.model = fmu.cs_fmu->new_instance();

                fmu.model->setup_experiment();
                fmu.model->enter_initialization_mode();
                fmu.model->exit_initialization_mode();
                // Set up data managers for different types

                // apply parameter sets

                // set start values?
            }
        }
    };

}