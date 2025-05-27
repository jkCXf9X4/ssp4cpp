
#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <stdexcept>

namespace ssp4cpp::common::json
{

    using Json = nlohmann::json;

    inline Json parse_json(const std::string &s)
    {
        return Json::parse(s);
    }

    inline std::string to_string(const Json &j)
    {
        return j.dump();
    }

    inline Json parse_json_file(const std::string &filename)
    {
        std::ifstream in(filename);
        if (!in)
        {
            throw std::runtime_error("Could not open file: " + filename);
        }
        return Json::parse(in);
    }

}
