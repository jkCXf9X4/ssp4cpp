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

    vector<pair<string, Fmu>> create_fmus(ssp4cpp::Ssp &ssp)
    {
        auto items = vector<pair<string, Fmu>>();

        for (auto &resource : ssp4cpp::ssp1::ext::ssd::get_resources(ssp.ssd))
        {
            auto name = resource->name.value_or("null");
            log.debug("Resource {}", name);

            auto fmu = ssp4cpp::Fmu(ssp.dir / resource->source);
            items.emplace_back(make_pair(name, fmu));
        }

        log.debug("FMUs");
        for (auto &[name, fmu] : items)
        {
            log.debug("{} : {}", name, fmu.to_string());
        }
        return items;
    }

    map<string, Fmu> create_fmu_map(ssp4cpp::Ssp &ssp)
    {
        auto fmus = create_fmus(ssp);

        return map_from_pairs(fmus);
    }

}