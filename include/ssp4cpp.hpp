#pragma once

#include <string>
#include <filesystem>

#include "ssp1/SystemStructureDescription.hpp"

namespace fs = std::filesystem;
using namespace std;

namespace ssp4cpp::ssp1
{
    optional<fs::path> open_ssp(const string &fileName);

    ssd::SystemStructureDescription parse_system_structure(const string &fileName);
}