#pragma once

#include "common_log.hpp"

#include "SSP1_SystemStructureDescription.hpp"

#include <string>
#include <vector>
#include <set>

namespace ssp4cpp::ssp1::ext
{
    using namespace ssp4cpp::ssp1::ssd;
    inline auto log = common::Logger("ssp1.ext", common::LogLevel::debug);

    namespace ssd
    {
        inline auto log = common::Logger("ssp1.ext.ssd", common::LogLevel::debug);

        std::vector<TComponent *> get_resources(const ssp1::ssd::SystemStructureDescription &ssd);
    }

    namespace elements
    {
        inline auto log = common::Logger("ssp1.ext.elements", common::LogLevel::debug);

        using IndexConnectorComponentTuple = tuple<int, Connector *, TComponent *>;
        using IndexConnectorComponentTuples = vector<IndexConnectorComponentTuple>;

        IndexConnectorComponentTuples get_connectors(Elements &elements);

        IndexConnectorComponentTuples get_connectors(
            Elements &elements,
            std::initializer_list<fmi2::md::Causality> causalities);

        // Get connections between fmus
        // return a set of <source_fmu, target_fmu> strings
        inline set<pair<string, string>> get_fmu_connections(const ssp1::ssd::SystemStructureDescription &ssd)
        {
            auto fmu_connections = set<pair<string, string>>();
            if (ssd.System.Connections.has_value())
            {
                for (auto connection : ssd.System.Connections.value().Connections)
                {
                    auto p = std::make_pair(connection.startElement.value(), connection.endElement.value());
                    fmu_connections.insert(p);
                }
            }
            return fmu_connections;
        }
    }

}
