#pragma once

#include <memory>
#include <string>
#include <pugixml.hpp>

#include "ssp1/SystemStructureDescription.hpp"

namespace ssp4cpp::ssp1::ssd
{
    void to_xml(pugi::xml_node &node, const Connector &connector);
    void to_xml(pugi::xml_node &node, const TConnectors &connectors);
    void to_xml(pugi::xml_node &node, const Connection &connection);
    void to_xml(pugi::xml_node &node, const Connections &connections);

    void to_xml(pugi::xml_node &node, const ElementGeometry &geometry);
    void to_xml(pugi::xml_node &node, const TParameterBindings &bindings);
    void to_xml(pugi::xml_node &node, const Elements &elements);
    void to_xml(pugi::xml_node &node, const TSignalDictionaries &dictionaries);
    void to_xml(pugi::xml_node &node, const SystemGeometry &geometry);
    void to_xml(pugi::xml_node &node, const GraphicalElements &elements);
    void to_xml(pugi::xml_node &node, const TDefaultExperiment &experiment);
    void to_xml(pugi::xml_node &node, const SystemStructureDescription &ssd);
    void to_xml(pugi::xml_node &node, const TSystem &system);
    void to_xml(pugi::xml_node &node, const TComponent &component);
    void to_xml(pugi::xml_node &node, const TSignalDictionaryReference &ref);

    void from_xml(const pugi::xml_node &node, Connector &connector);
    void from_xml(const pugi::xml_node &node, TConnectors &connectors);
    void from_xml(const pugi::xml_node &node, Connection &connection);
    void from_xml(const pugi::xml_node &node, Connections &connections);

    void from_xml(const pugi::xml_node &node, ElementGeometry &geometry);
    void from_xml(const pugi::xml_node &node, TParameterBindings &bindings);
    void from_xml(const pugi::xml_node &node, Elements &elements);
    void from_xml(const pugi::xml_node &node, TSignalDictionaries &dictionaries);
    void from_xml(const pugi::xml_node &node, SystemGeometry &geometry);
    void from_xml(const pugi::xml_node &node, GraphicalElements &elements);
    void from_xml(const pugi::xml_node &node, TDefaultExperiment &experiment);
    void from_xml(const pugi::xml_node &node, SystemStructureDescription &ssd);
    void from_xml(const pugi::xml_node &node, TSystem &system);
    void from_xml(const pugi::xml_node &node, TComponent &component);
    void from_xml(const pugi::xml_node &node, TSignalDictionaryReference &ref);
    
}

namespace ssp4cpp::ssp1::ssc
{
    void to_xml(pugi::xml_node &node, const TAnnotations &annotations);
    void to_xml(pugi::xml_node &node, const TEnumerations &enumerations);
    void to_xml(pugi::xml_node &node, const TUnits &units);

    void from_xml(const pugi::xml_node &node, TAnnotations &annotations);
    void from_xml(const pugi::xml_node &node, TEnumerations &enumerations);
    void from_xml(const pugi::xml_node &node, TUnits &units);
}


