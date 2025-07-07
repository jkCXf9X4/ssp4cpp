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

        // Borrowing
        ssp4cpp::Fmu *fmu;

        // Owning
        unique_ptr<fmi4cpp::fmi2::fmu> fmi4cpp_fmu;
        unique_ptr<fmi4cpp::fmi2::cs_fmu> cs_fmu;
        unique_ptr<fmi4cpp::fmi2::cs_slave> model;
        std::shared_ptr<const fmi4cpp::fmi2::cs_model_description> model_description;

        FmuInfo(std::string name, ssp4cpp::Fmu *fmu)
        {
            this->model_name = fmu->md.modelName;
            this->system_name = name;
            
            this->fmu = fmu;

            this->fmi4cpp_fmu = make_unique<fmi4cpp::fmi2::fmu>(this->fmu->original_file);
            this->cs_fmu = this->fmi4cpp_fmu->as_cs_fmu();
            this->model_description = this->cs_fmu->get_model_description();
        }
        // can not be copied, has unique pointers
        FmuInfo(const FmuInfo &) = delete;
        FmuInfo &operator=(const FmuInfo &) = delete;
    };

    class FmuHandler
    {
    public:
        common::Logger log = common::Logger("sim::FmuHandler", common::LogLevel::debug);

        map<string, unique_ptr<FmuInfo>> fmus;

        FmuHandler(std::map<std::string, ssp4cpp::Fmu *> &str_fmu)
        {
            for (auto &[name, fmu] : str_fmu)
            {
                fmus.emplace(name, make_unique<FmuInfo>(name, fmu));
            }
        }

        void init()
        {
            log.trace("[{}] Model init ", __func__);
            for (auto &[_, fmu] : this->fmus)
            {
                fmu->model = fmu->cs_fmu->new_instance();
                
                fmu->model->setup_experiment();
                fmu->model->enter_initialization_mode();
                fmu->model->exit_initialization_mode();
                // Set up data managers for different types
                
                // apply parameter sets
                
                // set start values?
            }
            log.trace("[{}] Model init completed", __func__);
        }
    };

}