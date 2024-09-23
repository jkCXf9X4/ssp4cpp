#pragma once

#include <pugixml.hpp>

#include "ssp1/SystemStructureCommon.hpp"

using namespace pugi;
namespace ssp4cpp::ssp1::ssc
{
    void from_xml(const xml_node &node, Annotation &obj);
    void from_xml(const xml_node &node, TAnnotations &obj);
    void from_xml(const xml_node &node, LinearTransformation &obj);
    void from_xml(const xml_node &node, BooleanMapEntry &obj);
    void from_xml(const xml_node &node, BooleanMappingTransformation &obj);
    void from_xml(const xml_node &node, IntegerMapEntry &obj);
    void from_xml(const xml_node &node, IntegerMappingTransformation &obj);
    void from_xml(const xml_node &node, EnumerationMapEntry &obj);
    void from_xml(const xml_node &node, EnumerationMappingTransformation &obj);
    void from_xml(const xml_node &node, Item &obj);
    void from_xml(const xml_node &node, TEnumeration &obj);
    void from_xml(const xml_node &node, TEnumerations &obj);
    void from_xml(const xml_node &node, BaseUnit &obj);
    void from_xml(const xml_node &node, TUnit &obj);
    void from_xml(const xml_node &node, TUnits &obj);
    void from_xml(const xml_node &node, GTypeReal &obj);
    void from_xml(const xml_node &node, GTypeInteger &obj);
    void from_xml(const xml_node &node, GTypeBoolean &obj);
    void from_xml(const xml_node &node, GTypeString &obj);
    void from_xml(const xml_node &node, GTypeEnumeration &obj);
    void from_xml(const xml_node &node, GTypeBinary &obj);

}
