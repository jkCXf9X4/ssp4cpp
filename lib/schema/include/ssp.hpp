#pragma once

#include "common_log.hpp"

#include "archive.hpp"

#include "SSP1_SystemStructureDescription.hpp"
#include "SSP1_SystemStructureDescription_Ext.hpp"
#include "SSP1_SystemStructureParameter_Ext.hpp"

#include <string>
#include <vector>
#include <optional>
#include <sstream>

namespace ssp4cpp
{
    /**
     * @brief Represents an SSP archive and its parsed SystemStructureDescription.
     */
    class Ssp : public Archive
    {

    public:
        std::unique_ptr<ssp1::ssd::SystemStructureDescription> ssd;

        std::map<std::string, ssp1::ext::ssv::Parameter> parameter_map;

        /**
         * @brief Construct an Ssp from a file path.
         */
        Ssp(const std::filesystem::path &file);

        virtual void print(std::ostream &os) const
        {
            auto resources = ssp1::ext::ssd::get_resources(*ssd);

            os << "Ssp { \n"
               << "original_file: " << original_file << std::endl
               << "dir: " << dir << std::endl
               << "ssd: " << ssd->name << std::endl
               << "resources: " << resources.size() << std::endl
               << " }" << std::endl;

            for (auto &res : resources)
            {
                os << "Resource: " << res->name.value_or("null") << std::endl;
            }
        }
    };

}
