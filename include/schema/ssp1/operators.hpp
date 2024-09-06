#pragma once

#include "ssp1/SystemStructureDescription.hpp"

namespace ssp4cpp::ssp1::ssd
{
    std::ostream &operator<<(std::ostream &os, const Connection &conn);
    std::ostream &operator<<(std::ostream &os, const Connections &conns);
    std::ostream &operator<<(std::ostream &os, const Connector &conn);
    std::ostream &operator<<(std::ostream &os, const TConnectors &conns);
    std::ostream &operator<<(std::ostream &os, const ComponentKind &kind);
    std::ostream &operator<<(std::ostream &os, const TComponent &comp);
    std::ostream &operator<<(std::ostream &os, const TSignalDictionaryReference &ref);
    std::ostream &operator<<(std::ostream &os, const Elements &elems);
    std::ostream &operator<<(std::ostream &os, const TSystem &sys);
    std::ostream &operator<<(std::ostream &os, const SystemStructureDescription &ssd);

}

namespace ssp4cpp::ssp1::ssc
{

}


