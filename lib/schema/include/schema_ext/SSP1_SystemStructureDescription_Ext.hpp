#pragma once

#include "common_log.hpp"

#include "SSP1_SystemStructureDescription.hpp"

#include <string>
#include <vector>

namespace ssp4cpp::ssp1::ext
{
    using namespace ssp4cpp::ssp1::ssd;

    namespace ssd
    {
        inline auto log = common::Logger("ssp1.ext.ssd", common::LogLevel::debug);

        std::vector<TComponent*> get_resources(const ssp1::ssd::SystemStructureDescription& ssd);

    }

    namespace elements
    {
        inline auto log = common::Logger("ssp1.ext.elements", common::LogLevel::debug);

        using IndexConnectorComponentTuple = tuple<int, Connector*, TComponent*>;
        using IndexConnectorComponentTuples = vector<IndexConnectorComponentTuple>;

        IndexConnectorComponentTuples get_connectors(Elements &elements);

        IndexConnectorComponentTuples get_connectors(
            Elements &elements,
            std::initializer_list<fmi2::md::Causality> causalities);
    }

}
