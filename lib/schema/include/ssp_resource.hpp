#pragma once

#include "SSP1_SystemStructureDescription.hpp"
#include "common_string.hpp"

#include <filesystem>
#include <string>
#include <vector>
#include <optional>

using namespace ssp4cpp::common::str;
using namespace std::filesystem;

// The goal is to limit this lib to only the schema, any custom types should be moved elsewhere
// Lift out this one to the sim library when possible

namespace ssp4cpp
{
    class SspResource
    {
    public:
        optional<ssp1::ssd::ComponentType> type;
        optional<string> name;
        string file;

        friend ostream &operator<<(ostream &os, const SspResource &obj)
        {
            os << "SspResource { \n"
               << "type: " << to_str(obj.type) << endl
               << "name: " << to_str(obj.name) << endl
               << "file: " << to_str(obj.file) << endl
               << " }" << endl;
            return os;
        }

        static std::vector<SspResource> parse_resources(ssp1::ssd::SystemStructureDescription ssd, path temp_dir)
        {
            std::vector<SspResource> resources;

            auto elements = ssd.System.Elements;
            if (elements)
            {
                for (auto comp : elements.value().Components)
                {
                    SspResource res;
                    res.type = comp.type;
                    res.name = comp.name;
                    res.file = temp_dir / comp.source;
                    resources.push_back(res);
                }
            }
            return resources;
        }
    };
}