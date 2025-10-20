#pragma once

#include "utils/log.hpp"

#include "ssp.hpp"
#include "fmu.hpp"

#include <map>
#include <string>
#include <memory>

namespace ssp4cpp::ssp::ext
{
    inline auto log = Logger("ssp4cpp.ssp.ext", LogLevel::info);

    std::map<std::string, std::string> get_resource_map(ssp4cpp::Ssp &ssp);

    /**
     * @brief Create a map of FMU names to loaded Fmu objects.
     */
    std::map<std::string, std::unique_ptr<Fmu>> create_fmu_map(ssp4cpp::Ssp &ssp);

}