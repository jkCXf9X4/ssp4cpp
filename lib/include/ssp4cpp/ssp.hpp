#pragma once

#include "ssp4cpp/utils/log.hpp"

#include "ssp4cpp/fmu.hpp"

#include "ssp4cpp/utils/archive.hpp"
#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureDescription.hpp"

#include <string>
#include <vector>
#include <sstream>
#include <optional>

namespace ssp4cpp
{

    // /**
    //  * @brief Represents an SSP archive and its parsed SystemStructureDescription.
    //  */

    // struct ParameterBindings
    // {
    //     ssp1::ssv::ParameterSet ssv;
    //     std::optional<ssp1::ssm::ParameterMapping> ssm;
    // };

    class Ssp : public Archive
    {

    public:
        std::unique_ptr<ssp1::ssd::SystemStructureDescription> ssd;
        // std::map<std::string, std::unique_ptr<Fmu>> fmus;

        // std::vector<ParameterBindings> parameter_bindings;

        ssp4cpp::utils::log::Logger* log = nullptr;

        /**
         * @brief Construct an Ssp from a file path.
         */
        Ssp(const std::filesystem::path &file, std::string ssd_name = "SystemStructure.ssd");

        /**
         * @brief Load a .ssv parameter set from a path relative to the SSP directory.
         */
        ssp1::ssv::ParameterSet load_ssv(const std::string &relative_path) const;

        /**
         * @brief Load a .ssm parameter mapping from a path relative to the SSP directory.
         */
        ssp1::ssm::ParameterMapping load_ssm(const std::string &relative_path) const;

        std::string to_string() const override
        {
            std::ostringstream oss;
            oss << "Ssp {"
               << "\noriginal_file: " << original_file
               << "\ndir: " << dir
               << "\nssd: " << ssd->name << "\n";

            // for (auto &[name, fmu] : fmus)
            // {
            //     oss << "FMU: " << name << "\n";
            // }
            oss << "\n }\n";
            return oss.str();
        }
    };

}
