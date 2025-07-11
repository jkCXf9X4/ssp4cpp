
#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <stdexcept>

namespace ssp4cpp::common::json
{

    using Json = nlohmann::json;

    /**
     * @brief Parse a JSON string into a Json object.
     */
    inline Json parse_json(const std::string &s)
    {
        return Json::parse(s);
    }

    /**
     * @brief Serialize a Json object to a string.
     */
    inline std::string to_string(const Json &j)
    {
        return j.dump();
    }

    /**
     * @brief Load and parse a JSON file.
     */
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
