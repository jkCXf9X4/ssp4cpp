
#pragma once

#include <nlohmann/json.hpp>
#include <string>


namespace ssp4cpp::common::json
{

    using Json = nlohmann::json;

    /**
     * @brief Parse a JSON string into a Json object.
     */
    Json parse_json(const std::string &s);

    /**
     * @brief Serialize a Json object to a string.
     */
    std::string to_string(const Json &j);

    /**
     * @brief Load and parse a JSON file.
     */
    Json parse_json_file(const std::string &filename);

}
