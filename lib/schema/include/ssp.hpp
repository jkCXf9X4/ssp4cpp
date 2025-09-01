#pragma once

#include "common_log.hpp"

#include "archive.hpp"

#include "SSP1_SystemStructureDescription.hpp"
#include "SSP1_SystemStructureDescription_Ext.hpp"

#include <string>
#include <vector>
#include <optional>
#include <sstream>

namespace ssp4cpp
{
    using namespace std::filesystem;
    
    using namespace ssp4cpp::common::str;
    using namespace common;


    class Parameters
    {
        std::string name;
        fmi2::md::Type type;
        std::unique_ptr<std::byte[]> initial_value;
    };

    struct Bindings
    {
        std::unique_ptr<ssp1::ssv::ParameterSet> ssv;
        std::unique_ptr<ssp1::ssm::ParameterMapping> ssm;
        std::vector<Parameters> parameters;
    };

    /**
     * @brief Represents an SSP archive and its parsed SystemStructureDescription.
     */
    class Ssp : public Archive
    {
    public:
        unique_ptr<ssp1::ssd::SystemStructureDescription> ssd;
        std::vector<Bindings> bindings;

        /**
         * @brief Construct an Ssp from a file path.
         */
        Ssp(const path &file);

        friend ostream &operator<<(ostream &os, const Ssp &obj)
        {
            auto resources = ssp1::ext::ssd::get_resources(*obj.ssd);

            os << "Ssp { \n"
               << "original_file: " << obj.original_file << endl
               << "dir: " << obj.dir << endl
               << "ssd: " << obj.ssd->name << endl
               << "resources: " << resources.size() << endl
               << " }" << endl;

            for (auto &res : resources)
            {
                os << "Resource: " << res->name.value_or("null") << endl;
            }
            return os;
        }

        /** @brief Convert to string for debugging purposes. */
        std::string to_string();
    };

}
