#pragma once

#include "SSP1_SystemStructureDescription.hpp"
#include "common_string.hpp"
#include "common_log.hpp"

#include <string>
#include <vector>
#include <filesystem>
#include <optional>
#include <sstream>

using namespace std;
using namespace std::filesystem;
using namespace ssp4cpp::common::str;

namespace ssp4cpp::ssp1
{

    class SspResource
    {
    public:
        optional<ssd::ComponentType> type;
        optional<string> name;
        string file;

        friend ostream &operator<<(ostream &os, const SspResource &obj)
        {
            os << "SspResource { \n"
               << "type: " << to_str(obj.type)  << endl
               << "name: " << to_str(obj.name) << endl
               << "file: " << to_str(obj.file) << endl
               << " }" << endl;
            return os;
        }
    };

    class SspImport
    {
    public:
        path original_file;
        path temp_dir;
        ssd::SystemStructureDescription ssd;
        vector<SspResource> resources;
        common::Logger log;

        SspImport(const path &file);

        ~SspImport();

        friend ostream &operator<<(ostream &os, const SspImport &obj)
        {
            os << "SspImport { \n"
               << "original_file: " << obj.original_file << endl
               << "temp_dir: " << obj.temp_dir << endl
               << "ssd: " << obj.ssd.name << endl
               << "resources: " << obj.resources.size() << endl
               << " }" << endl;

               for (const auto &res : obj.resources)
               {
                   os << res << endl;
               }
            return os;
        }

        std::string to_str()
        {
            return common::str::stream_to_str(this);
        }

    private:
        ssd::SystemStructureDescription parse_system_structure(const string &fileName);
    };

}
