#include "SystemStructureDescription.hpp"
#include "schema/ssp1/xml_functions.hpp"
#include "schema/ssp1/operators.hpp"
#include "xml_misc.cpp"

#include <iostream>

namespace ssp4cpp::ssp1::ssd
{
    // std::ostream &operator<<(std::ostream &os, const ComponentKind &kind)
    // {
    //     switch (kind)
    //     {
    //     case ComponentKind::XFmuSharedlibrary:
    //         os << "XFmuSharedlibrary";
    //         break;
    //     case ComponentKind::XSspDefinition:
    //         os << "XSspDefinition";
    //         break;
    //     case ComponentKind::XSspPackage:
    //         os << "XSspPackage";
    //         break;
    //     }
    //     return os;
    // }

    // std::ostream &operator<<(std::ostream &os, const TComponent &comp)
    // {
    //     os << "TComponent(id: " << comp.id.value_or("null")
    //        << ", description: " << comp.description.value_or("null")
    //        << ", name: " << comp.name.value_or("null")
    //        << ", source: " << comp.source
    //        << ", implementation: " << comp.implementation.value_or("null") << ")";
    //     return os;
    // }


}