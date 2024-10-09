

#include "SystemStructureDescription.hpp"

#include <string>
#include <vector>


namespace ssp4cpp::ssp1::ssd
{
    // using IndexDependencyCoupling = std::tuple<int, int, DependenciesKind>;

    class TConnectors_Ext
    {
    public:
        // get_connectors(&connectors, {Causality::input, Causality::output})
        static vector<reference_wrapper<Connector>> get_connectors(TConnectors &connectors, std::initializer_list<fmi2::Causality> causalities);

    };



}
