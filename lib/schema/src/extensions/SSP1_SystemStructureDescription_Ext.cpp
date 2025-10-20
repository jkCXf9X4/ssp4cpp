
#include "SSP1_SystemStructureDescription_Ext.hpp"

#include "utils/string.hpp"
#include "utils/vector.hpp"

#include <vector>
#include <tuple>
#include <optional>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <ranges>

using namespace std;
using namespace ssp4cpp::ssp1;
using namespace ssp4cpp::common::str;
using namespace ssp4cpp::common;
namespace views = std::ranges::views;

namespace ssp4cpp::ssp1::ext
{
    using namespace ssp4cpp::ssp1::ssd;

    namespace ssd
    {
        std::vector<TComponent*> get_resources(const ssp1::ssd::SystemStructureDescription& ssd)
        {
            auto resources = vector<TComponent*>();

            if (ssd.System.Elements.has_value())
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
        IndexConnectorComponentTuples get_connectors(Elements &elements)
        {
            int i = 0;
            auto cs = IndexConnectorComponentTuples();

            for (auto &component : elements.Components)
            {
                if (component.Connectors.has_value())
                {
                    for (auto &connector : component.Connectors.value().Connectors)
                    {
                        cs.push_back(make_tuple(i, &connector, &component));
                        i++;
                    }
                }
            }

            return cs;
        }

        static void reset_index(IndexConnectorComponentTuples &tuples)
        {
            int i = 0;
            for (auto &[index, connection, component] : tuples)
            {
                index = i;
                i++;
            }
        }

        IndexConnectorComponentTuples get_connectors(
            Elements &elements,
            std::initializer_list<fmi2::md::Causality> causalities)
        {
            auto in = get_connectors(elements);
            auto out = IndexConnectorComponentTuples();

            std::copy_if(begin(in), end(in), std::back_inserter(out),
                         [causalities](IndexConnectorComponentTuple a)
                         { return ssp4cpp::common::list::is_in_list(get<1>(a)->kind, causalities); });

            reset_index(out);

            return out;
        }

        set<pair<string, string>> get_fmu_connections(const ssp1::ssd::SystemStructureDescription &ssd)
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
