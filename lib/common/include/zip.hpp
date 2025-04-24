#pragma once

#include <filesystem>

// dont name this 'zip', collision between namespace and types makes life harder
namespace ssp4cpp::common::zip_ns
{
    namespace fs = std::filesystem;
    
    fs::path unzip_to_temp_dir(const std::string fileName, std::string pre);
}