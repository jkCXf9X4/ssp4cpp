#pragma once

#include "utils/log.hpp"

#include "SSP1_SystemStructureDescription.hpp"

#include <string>
#include <vector>
#include <set>

namespace ssp4cpp::ssp1::ext
{
    using namespace ssp4cpp::ssp1::ssd;
    inline auto log = utils::Logger("ssp1.ext", utils::LogLevel::debug);

    namespace ssd
    {
        inline auto log = utils::Logger("ssp4cpp.ssp1.ext.ssd", utils::LogLevel::debug);

        std::vector<TComponent *> get_resources(const ssp1::ssd::SystemStructureDescription &ssd);
    }

    namespace elements
    {
        inline auto log = utils::Logger("ssp4cpp.ssp1.ext.elements", utils::LogLevel::debug);

        using IndexConnectorComponentTuple = tuple<int, Connector *, TComponent *>;
        using IndexConnectorComponentTuples = vector<IndexConnectorComponentTuple>;

        IndexConnectorComponentTuples get_connectors(Elements &elements);

        IndexConnectorComponentTuples get_connectors(
            Elements &elements,
            std::initializer_list<fmi2::md::Causality> causalities);

        // Get connections between fmus
        // return a set of <source_fmu, target_fmu> strings
        set<pair<string, string>> get_fmu_connections(const ssp1::ssd::SystemStructureDescription &ssd);
    }

}
