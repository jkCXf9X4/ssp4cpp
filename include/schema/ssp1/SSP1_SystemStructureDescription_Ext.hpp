

#include "SSP1_SystemStructureDescription.hpp"

#include <string>
#include <vector>

namespace ssp4cpp::ssp1::ssd
{
    using IndexConnectorComponentTuple = tuple<int, Connector &, TComponent &>;

    class Elements_Ext
    {
    public:
        static vector<IndexConnectorComponentTuple> get_connectors(Elements &elements);

        // get_connectors(&Elements, {Causality::input, Causality::output})
        static vector<IndexConnectorComponentTuple> get_connectors(
            Elements &elements,
            std::initializer_list<fmi2::md::Causality> causalities);
    };

}
