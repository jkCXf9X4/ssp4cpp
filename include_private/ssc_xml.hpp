#pragma once

#include <pugixml.hpp>

#include "ssp1/SystemStructureCommon.hpp"

namespace ssp4cpp::ssp1::ssc
{
    using namespace pugi;

    void from_xml(const xml_node &node, TAnnotations &annotations);
    void from_xml(const xml_node &node, TEnumerations &enumerations);
    void from_xml(const xml_node &node, TUnits &units);
    void from_xml(const xml_node &node, GTypeReal &real);
    void from_xml(const xml_node &node, GTypeInteger &integer);
    void from_xml(const xml_node &node, GTypeBoolean &boolean);
    void from_xml(const xml_node &node, GTypeString &string);
    void from_xml(const xml_node &node, GTypeEnumeration &enumeration);
    void from_xml(const xml_node &node, GTypeBinary &binary);
    void from_xml(const xml_node &node, LinearTransformation &transform);

    void from_xml(const xml_node &node, BooleanMappingTransformation &transform);
    void from_xml(const xml_node &node, IntegerMappingTransformation &transform);
    void from_xml(const xml_node &node, EnumerationMappingTransformation &transform);
    
    void from_xml(const xml_node &node, BooleanMapEntry &entry);
    void from_xml(const xml_node &node, IntegerMapEntry &entry);
    void from_xml(const xml_node &node, EnumerationMapEntry &entry);
}


