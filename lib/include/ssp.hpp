#pragma once

#include "cutecpp/log.hpp"

#include "archive.hpp"

#include "SSP1_SystemStructureDescription.hpp"

#include <string>
#include <vector>
#include <optional>
#include <sstream>

namespace ssp4cpp
{

    /**
     * @brief Represents an SSP archive and its parsed SystemStructureDescription.
     */

    struct ParameterBindings
    {
        std::unique_ptr<ssp1::ssv::ParameterSet> ssv;
        std::unique_ptr<ssp1::ssm::ParameterMapping> ssm;
    };

    class Ssp : public Archive
    {

    public:
        std::unique_ptr<ssp1::ssd::SystemStructureDescription> ssd;
        std::vector<ssp1::ssd::TComponent *> resources;
        std::vector<ParameterBindings> parameter_bindings;

        /**
         * @brief Construct an Ssp from a file path.
         */
        Ssp(const std::filesystem::path &file);

        virtual void print(std::ostream &os) const
        {
            auto resources = get_resources(*ssd);

            os << "Ssp {"
               << "\noriginal_file: " << original_file
               << "\ndir: " << dir
               << "\nssd: " << ssd->name
               << "\nresources: " << resources.size()
               << "\n }\n";

            for (auto &res : resources)
            {
                os << "Resource: " << res->name.value_or("null") << "\n";
            }
        }

    private:

        std::vector<ssp1::ssd::TComponent *> get_resources(const ssp1::ssd::SystemStructureDescription &ssd) const;

        std::vector<ParameterBindings> get_parameter_bindings(std::filesystem::path &dir, ssp1::ssd::SystemStructureDescription &ssd);
    };

}
