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

        
        inline std::vector<TComponent*> get_resources(const ssp1::ssd::SystemStructureDescription& ssd)
        {
            auto resources = vector<TComponent*>();

            if (ssd.System.Elements)
            {
                for (auto &comp : ssd.System.Elements.value().Components)
                {
                    // Make sure that the object is cast as a non const
                    resources.push_back(const_cast<TComponent*>(&comp));
                }
            }
            return resources;
        }
    }

    namespace elements
    {
        inline auto log = common::Logger("ssp1.ext.elements", common::LogLevel::debug);

        using IndexConnectorComponentTuple = tuple<int, reference_wrapper<Connector>, reference_wrapper<TComponent>>;
        using IndexConnectorComponentTuples = vector<IndexConnectorComponentTuple>;

        IndexConnectorComponentTuples get_connectors(Elements &elements);

        IndexConnectorComponentTuples get_connectors(
            Elements &elements,
            std::initializer_list<fmi2::md::Causality> causalities);
    }

}
