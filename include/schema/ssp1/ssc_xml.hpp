#pragma once

#include <pugixml.hpp>

#include "ssp1/SystemStructureCommon.hpp"

namespace ssp4cpp::ssp1::ssc
{
    void to_xml(pugi::xml_node &node, const TAnnotations &annotations);
    void to_xml(pugi::xml_node &node, const TEnumerations &enumerations);
    void to_xml(pugi::xml_node &node, const TUnits &units);

    void from_xml(const pugi::xml_node &node, TAnnotations &annotations);
    void from_xml(const pugi::xml_node &node, TEnumerations &enumerations);
    void from_xml(const pugi::xml_node &node, TUnits &units);
}


