#pragma once

#include <memory>
#include <string>

#include "ssp1/SystemStructureDescription.hpp"

namespace ssp4cpp::ssp1::ssd
{
    std::unique_ptr<SystemStructureDescription> parse_system_structure(const std::string &fileName);
}


