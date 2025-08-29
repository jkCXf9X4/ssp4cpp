#pragma once

#include "common_log.hpp"

#include "archive.hpp"

#include "SSP1_SystemStructureDescription.hpp"
#include "SSP1_SystemStructureDescription_Ext.hpp"

#include <string>
#include <vector>
#include <optional>
#include <sstream>

using namespace std;
using namespace std::filesystem;

using namespace ssp4cpp::common::str;

namespace ssp4cpp
{
    using namespace common;

    struct Bindings
    {
        ssp1::ssv::ParameterSet ssv;
        optional<ssp1::ssm::ParameterMapping> ssm;
    };

    /**
     * @brief Represents an SSP archive and its parsed SystemStructureDescription.
     */
    class Ssp : public Archive
    {
    public:
        ssp1::ssd::SystemStructureDescription ssd;
        vector<Bindings> bindings;

        /**
         * @brief Construct an Ssp from a file path.
         */
        Ssp(const path &file);

        friend ostream &operator<<(ostream &os, const Ssp &obj)
        {
            auto resources = ssp1::ext::ssd::get_resources(obj.ssd);

            os << "Ssp { \n"
               << "original_file: " << obj.original_file << endl
               << "dir: " << obj.dir << endl
               << "ssd: " << obj.ssd.name << endl
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
