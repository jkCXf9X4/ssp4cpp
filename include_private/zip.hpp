#pragma once

#include <filesystem>

namespace ssp4cpp::zip_ns
{
    std::filesystem::path unzip_to_temp_dir(const std::string &fileName);
}