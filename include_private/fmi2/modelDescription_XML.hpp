#pragma once

#include <pugixml.hpp>

#include "modelDescription.hpp"

using namespace pugi;

namespace ssp4cpp::fmi2
{
    void from_xml(const xml_node &node, BaseUnit &obj);
    void from_xml(const xml_node &node, DisplayUnit &obj);
    void from_xml(const xml_node &node, fmi2Unit &obj);
    void from_xml(const xml_node &node, UnitDefinitions &obj);
    void from_xml(const xml_node &node, Boolean &obj);
    void from_xml(const xml_node &node, Integer &obj);
    void from_xml(const xml_node &node, String &obj);
    void from_xml(const xml_node &node, Real &obj);
    void from_xml(const xml_node &node, Enumeration &obj);
    void from_xml(const xml_node &node, SimpleTypeEnumerationItem &obj);
    void from_xml(const xml_node &node, SimpleTypeEnumeration &obj);
    void from_xml(const xml_node &node, fmi2SimpleType &obj);
    void from_xml(const xml_node &node, TypeDefinitions &obj);
    void from_xml(const xml_node &node, Category &obj);
    void from_xml(const xml_node &node, LogCategories &obj);
    void from_xml(const xml_node &node, fmi2Annotation &obj);
    void from_xml(const xml_node &node, VendorAnnotations &obj);
    void from_xml(const xml_node &node, DefaultExperiment &obj);
    void from_xml(const xml_node &node, fmi2ScalarVariable &obj);
    void from_xml(const xml_node &node, unknown &obj);
    void from_xml(const xml_node &node, ModelStructure &obj);
    void from_xml(const xml_node &node, ModelVariables &obj);
    void from_xml(const xml_node &node, File &obj);
    void from_xml(const xml_node &node, ModelExchange &obj);
    void from_xml(const xml_node &node, CoSimulation &obj);
    void from_xml(const xml_node &node, fmi2ModelDescription &obj);
}

