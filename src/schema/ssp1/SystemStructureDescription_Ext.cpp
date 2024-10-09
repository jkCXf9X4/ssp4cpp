
#include "SystemStructureDescription_Ext.hpp"

#include <optional>
#include <iostream>
#include <initializer_list>
#include <algorithm>

using namespace std;
using namespace ssp4cpp::ssp1;
using namespace ssp4cpp::str;

namespace ssp4cpp::ssp1::ssd
{
    vector<reference_wrapper<Connector>> TConnectors_Ext::get_connectors(TConnectors &connectors, std::initializer_list<fmi2::Causality> causalities)
    {
        auto cs = vector<reference_wrapper<Connector>>();
        for (auto &connector : connectors.Connectors)
        {
            if (std::find(causalities.begin(), causalities.end(), connector.kind) != causalities.end())
            {
                cs.push_back(connector);
            }
        }
        return cs;
    }

}
