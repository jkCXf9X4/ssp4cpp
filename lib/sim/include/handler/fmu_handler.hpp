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

        // Owning
        std::unique_ptr<fmi4cpp::fmi2::fmu> fmi4cpp_fmu;
        std::unique_ptr<fmi4cpp::fmi2::cs_fmu> cs_fmu;
        std::unique_ptr<fmi4cpp::fmi2::cs_slave> model;
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

        map<string, std::unique_ptr<FmuInfo>> fmus;
        ssp4cpp::Ssp *ssp;

        FmuHandler(std::map<std::string, ssp4cpp::Fmu *> &str_fmu, ssp4cpp::Ssp *ssp)
        {
            for (auto &[name, fmu] : str_fmu)
            {
                fmus.emplace(name, make_unique<FmuInfo>(name, fmu));
            }
            this->ssp = ssp;
        }

        void apply_start_values(fmi4cpp::fmi2::cs_slave* model)
        {
            for (auto &binding: ssp->bindings)
            {

            }
        }

        void init()
        {
            log.trace("[{}] Model init ", __func__);
            for (auto &[_, fmu] : this->fmus)
            {
                fmu->model = fmu->cs_fmu->new_instance();

                apply_start_values(fmu->model.get());

                fmu->model->setup_experiment();
                fmu->model->enter_initialization_mode();
                fmu->model->exit_initialization_mode();
            }
            log.trace("[{}] Model init completed", __func__);
        }
    };

}