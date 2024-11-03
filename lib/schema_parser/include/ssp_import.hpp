#pragma once

#include "SSP1_SystemStructureDescription.hpp"
#include "to_string.hpp"

#include <string>
#include <vector>
#include <filesystem>
#include <optional>

using namespace std;
using namespace std::filesystem;

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
               << "type: " << str::to_str(obj.type)  << endl
               << "name: " << str::to_str(obj.name) << endl
               << "file: " << str::to_str(obj.file) << endl
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

    private:
        ssd::SystemStructureDescription parse_system_structure(const string &fileName);
    };

}