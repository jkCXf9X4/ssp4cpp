#pragma once

#include <pugixml.hpp>

#include "ssp1/SystemStructureDescription.hpp"

namespace ssp4cpp::ssp1::ssd
{
    void from_xml(const pugi::xml_node &node, Connector &connector);
    void from_xml(const pugi::xml_node &node, TConnectors &connectors);
    void from_xml(const pugi::xml_node &node, Connection &connection);
    void from_xml(const pugi::xml_node &node, Connections &connections);

    void from_xml(const pugi::xml_node &node, ElementGeometry &geometry);
    void from_xml(const pugi::xml_node &node, ConnectorGeometry &geometry);
    void from_xml(const pugi::xml_node &node, ConnectionGeometry &geometry);
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



