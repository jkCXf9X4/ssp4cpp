
#pragma once

#include <string>

namespace ssp4cpp::common::io
{

    /**
     * @brief Write a string to a file, overwriting any existing content.
     */
    void save_string(const std::string &filename, const std::string &content);

}