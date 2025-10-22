

// This is a generated file, do not alter
// it is based on ssp1_ssd.toml

#pragma once

#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureDescription.hpp"
#include <pugixml.hpp>

namespace ssp4cpp::ssp1::ssd
{
    using namespace pugi;

    void from_xml(const xml_node &node, SystemGeometry &obj);

    void from_xml(const xml_node &node, ConnectorGeometry &obj);

    void from_xml(const xml_node &node, ElementGeometry &obj);

    void from_xml(const xml_node &node, ConnectionGeometry &obj);

    void from_xml(const xml_node &node, SignalDictionary &obj);

    void from_xml(const xml_node &node, TSignalDictionaries &obj);

    void from_xml(const xml_node &node, ParameterMapping &obj);

    void from_xml(const xml_node &node, ParameterBinding &obj);

    void from_xml(const xml_node &node, TParameterBindings &obj);

    void from_xml(const xml_node &node, GraphicalElements &obj);

    void from_xml(const xml_node &node, TDefaultExperiment &obj);

    void from_xml(const xml_node &node, Connection &obj);

    void from_xml(const xml_node &node, Connections &obj);

    void from_xml(const xml_node &node, Connector &obj);

    void from_xml(const xml_node &node, TConnectors &obj);

    void from_xml(const xml_node &node, TComponent &obj);

    void from_xml(const xml_node &node, TSignalDictionaryReference &obj);

    void from_xml(const xml_node &node, Elements &obj);

    void from_xml(const xml_node &node, TSystem &obj);

    void from_xml(const xml_node &node, SystemStructureDescription &obj);


}
