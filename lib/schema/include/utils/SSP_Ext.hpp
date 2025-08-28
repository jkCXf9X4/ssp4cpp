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
    inline auto log = common::Logger("ssp.ext", common::LogLevel::info);

    map<string,string> get_resource_map(ssp4cpp::Ssp &ssp)
    {
        auto resources = map<string,string>();

        for (auto &resource : ssp4cpp::ssp1::ext::ssd::get_resources(ssp.ssd))
        {
            auto name = resource->name.value_or("null");
            log.trace("Resource {} : {}", name, resource->source);

            resources[name] = resource->source;
        }
        return resources;
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
            log.trace("Resource {}", name);

            auto fmu = make_unique<ssp4cpp::Fmu>(ssp.dir / resource->source);
            items[name] = std::move(fmu);
        }

        log.trace("FMUs");
        for (auto &[name, fmu] : items)
        {
            log.trace("{} : {}", name, fmu->to_string());
        }
        return items;
    }

}