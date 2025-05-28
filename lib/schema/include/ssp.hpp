#pragma once

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

    class Ssp
    {
    public:
        Logger log = Logger("Ssp.Ssp", LogLevel::debug);
        bool using_tmp_dir = false;
        path original_file;
        path dir;
        ssp1::ssd::SystemStructureDescription ssd;

        Ssp(const path &file);
        

        Ssp() = delete;
        // Object is not copyable, 
        // this would create uncertainty of who own any file references
        Ssp(Ssp& obj) = delete;
        Ssp &operator=(const Ssp &other) = delete;

        ~Ssp();

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
