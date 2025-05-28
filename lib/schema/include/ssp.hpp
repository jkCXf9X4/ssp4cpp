#pragma once

#include "zip.hpp"
#include "archive.hpp"
#include "common_string.hpp"
#include "common_log.hpp"

#include "SSP1_SystemStructureDescription.hpp"
#include "SSP1_SystemStructureDescription_Ext.hpp"

#include <string>
#include <vector>
#include <filesystem>
#include <optional>
#include <sstream>

using namespace std;
using namespace std::filesystem;

using namespace ssp4cpp::common::str;

namespace ssp4cpp
{
    using namespace common;

    class Ssp : public Archive
    {
    public:
        ssp1::ssd::SystemStructureDescription ssd;

        Ssp(const path &file)
            : Archive(Logger("Ssp", LogLevel::debug), file, "ssp_")
        {
            ssd = parse_system_structure((dir / "SystemStructure.ssd").string());
            log.info("SSP Imported");
        }

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

        std::string to_string()
        {
            return common::str::stream_to_str(*this);
        }

    private:
        static ssp1::ssd::SystemStructureDescription parse_system_structure(const string &fileName);
    };

}
