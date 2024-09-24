#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <optional>

#include "ssp1/SystemStructureDescription.hpp"

using namespace std;
using namespace std::filesystem;

namespace ssp4cpp::ssp1
{

    class SspResource
    {
    public:
        // optional<string> type;
        optional<string> name;
        string file;

        friend ostream &operator<<(ostream &os, const SspResource &obj)
        {
            // string type = obj.type.has_value() ? to_string(obj.type.value()) : "null";
            os << "SspResource { \n"
            //    << "type: " << obj.type.value_or("null")  << endl
               << "name: " << obj.name.value_or("null") << endl
               << "file: " << obj.file << endl
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