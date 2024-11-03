#pragma once

#include <filesystem>

namespace ssp4cpp::zip_ns
{
    namespace fs = std::filesystem;
    fs::path unzip_to_temp_dir(const std::string fileName, std::string pre);
}