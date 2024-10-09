
#include "SSP1_SystemStructureDescription_Ext.hpp"

#include "misc.hpp"

#include <vector>
#include <tuple>
#include <optional>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <ranges>

using namespace std;
using namespace ssp4cpp::ssp1;
using namespace ssp4cpp::str;
namespace views = std::ranges::views;

namespace ssp4cpp::ssp1::ssd
{

    vector<IndexConnectorComponentTuple> Elements_Ext::get_connectors(Elements &elements)
    {
        int i = 0;
        auto cs = vector<IndexConnectorComponentTuple>();

        for (auto &component : elements.Components)
        {
            if (component.Connectors.has_value())
            {
                for (auto &connector : component.Connectors.value().Connectors)
                {
                    cs.push_back(make_tuple(i, std::ref(connector), std::ref(component)));
                    i++;
                }
            }
        }

        return cs;
    }

    // get_connectors(&Elements, {Causality::input, Causality::output})
    vector<IndexConnectorComponentTuple> Elements_Ext::get_connectors(
        Elements &elements,
        std::initializer_list<fmi2::md::Causality> causalities)
    {
        auto out = get_connectors(elements);

        std::erase_if(out, [causalities](IndexConnectorComponentTuple a)
                      { return !ssp4cpp::misc::enum_in_list(get<1>(a).kind, causalities); });

        return out;
    }
}
