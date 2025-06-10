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
    using namespace std;
    inline auto log = common::Logger("ssp.ext", common::LogLevel::debug);

    /**
     * @brief Retrieve the FMU resource names from the given SSP.
     */
    vector<string> get_fmu_names(ssp4cpp::Ssp &ssp)
    {
        auto names = vector<string>();

        for (auto &resource : ssp4cpp::ssp1::ext::ssd::get_resources(ssp.ssd))
        {
            auto name = resource->name.value_or("null");
            names.push_back(name);
            log.debug("Resource {}", name);
        }
        return names;
    }

    /**
     * @brief Create a map of FMU names to loaded Fmu objects.
     */
    map<string, unique_ptr<Fmu>> create_fmu_map(ssp4cpp::Ssp &ssp)
    {
        auto items = map<string, unique_ptr<Fmu>>();

        for (auto &resource : ssp4cpp::ssp1::ext::ssd::get_resources(ssp.ssd))
        {
            auto name = resource->name.value_or("null");
            log.debug("Resource {}", name);

            auto fmu = make_unique<ssp4cpp::Fmu>(ssp.dir / resource->source);
            items[name] = std::move(fmu);
        }

        log.debug("FMUs");
        for (auto &[name, fmu] : items)
        {
            log.debug("{} : {}", name, fmu->to_string());
        }
        return items;
    }

}