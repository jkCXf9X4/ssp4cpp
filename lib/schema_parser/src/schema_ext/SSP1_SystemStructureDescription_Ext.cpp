
#include "SSP1_SystemStructureDescription_Ext.hpp"


#include "common_string.hpp"
#include "common_list.hpp"


#include <vector>
#include <tuple>
#include <optional>
#include <iostream>
#include <initializer_list>
#include <algorithm>
#include <ranges>

using namespace std;
using namespace ssp4cpp::ssp1;
using namespace ssp4cpp::common::string;
namespace views = std::ranges::views;

namespace ssp4cpp::ssp1::ssd
{

    IndexConnectorComponentTuples Elements_Ext::get_connectors(Elements &elements)
    {
        int i = 0;
        auto cs = IndexConnectorComponentTuples();

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

    void reset_index(IndexConnectorComponentTuples& tuples)
    {
        int i = 0;
        for (auto& [index, connection, component] : tuples)
        {
            index = i;
            i++;
        }
    }

    // get_connectors(&Elements, {Causality::input, Causality::output})
    IndexConnectorComponentTuples Elements_Ext::get_connectors(
        Elements &elements,
        std::initializer_list<fmi2::md::Causality> causalities)
    {
        auto in = get_connectors(elements);
        auto out = IndexConnectorComponentTuples();

        std::copy_if(begin(in), end(in), std::back_inserter(out),
                     [causalities](IndexConnectorComponentTuple a)
                     { return ssp4cpp::common::list::is_in_list(get<1>(a).get().kind, causalities); });

        reset_index(out);

        return out;
    }
}
