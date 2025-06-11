#pragma once

#include "common_map.hpp"
#include "common_vector.hpp"

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
        ssp4cpp::Fmu *fmu;

        fmi4cpp::fmi2::fmu fmu2;
        unique_ptr<fmi4cpp::fmi2::cs_fmu> cs_fmu;
        unique_ptr<fmi4cpp::fmi2::cs_slave> model;
        std::shared_ptr<const fmi4cpp::fmi2::cs_model_description> model_description;
    };


    class FmuHandler
    {
    public:
        common::Logger log = common::Logger("sim::FmuHandler", common::LogLevel::ext_trace);

        map<string, FmuInfo> fmus;

        FmuHandler(std::map<std::string, ssp4cpp::Fmu *> &str_fmu)
        {
            for (auto &[name, fmu] : str_fmu)
            {
                FmuInfo f;
                f.model_name = fmu->md.modelName;
                f.system_name = name;
                f.fmu = fmu;

                f.fmu2 = fmi4cpp::fmi2::fmu(fmu->original_file);
                f.cs_fmu = f.fmu2.as_cs_fmu();
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