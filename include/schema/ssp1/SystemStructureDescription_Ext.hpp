
#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "SystemStructureDescription.hpp"
#include "to_string.hpp"

using namespace std;
using namespace ssp4cpp::ssp1;
using namespace ssp4cpp::str;

namespace ssp4cpp::ssp1::ssd
{
     class TConnectors_Ext
    {
    public:
        static vector<Connector&> get_connectors(TConnectors &connectors);
    };

}
