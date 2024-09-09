#pragma once

#include <filesystem>

namespace ssp4cpp::zip_ns
{
    bool unzip(std::filesystem::path &file, const std::filesystem::path &tmp_path);
}