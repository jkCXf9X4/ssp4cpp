#pragma once

#include "common_string.hpp"
#include "common_log.hpp"

#include "SSP1_SystemStructureDescription.hpp"
#include "ssp_resource.hpp"

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

    class Ssp
    {
    public:
        path original_file;
        path temp_dir;
        ssp1::ssd::SystemStructureDescription ssd;
        vector<SspResource> resources;
        common::Logger log;

        Ssp(const path &file);

        ~Ssp();

        friend ostream &operator<<(ostream &os, const Ssp &obj)
        {
            os << "Ssp { \n"
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
        static ssp1::ssd::SystemStructureDescription parse_system_structure(const string &fileName);
    };

}
