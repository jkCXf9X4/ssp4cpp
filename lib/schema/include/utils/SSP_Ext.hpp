#pragma once

#include "ssp.hpp"
#include "fmu.hpp"

#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

namespace ssp4cpp::ssp::ext
{
    inline auto log = common::Logger("ssp.ext", common::LogLevel::info);

    std::map<std::string,std::string> get_resource_map(ssp4cpp::Ssp &ssp);

    /**
     * @brief Create a map of FMU names to loaded Fmu objects.
     */
    std::map<std::string, std::unique_ptr<Fmu>> create_fmu_map(ssp4cpp::Ssp &ssp);

}