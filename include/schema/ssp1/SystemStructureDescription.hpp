#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "IXmlNode.hpp"

#include "SystemStructureCommon.hpp"

namespace ssp4cpp::ssp1::ssd
{
    class TSystem;

    class SystemGeometry : public IXmlNode
    {
    public:


        string to_string(void) const;
    };

    class ConnectorGeometry : public IXmlNode
    {
    public:


        string to_string(void) const;
    };

    class ElementGeometry : public IXmlNode
    {
    public:


        string to_string(void) const;
    };

    class ConnectionGeometry : public IXmlNode
    {
    public:


        string to_string(void) const;
    };

    class TSignalDictionaries : public IXmlNode
    {
    public:


        string to_string(void) const;
    };

    class TParameterBindings : public IXmlNode
    {
    public:


        string to_string(void) const;
    };

    class GraphicalElements : public IXmlNode
    {
    public:


        string to_string(void) const;
    };

    class TDefaultExperiment : public IXmlNode
    {
    public:


        string to_string(void) const;
    };

    class Connection : public IXmlNode
    {
    public:
        optional<string> startElement;
        string startConnector;
        optional<string> endElement;
        string endConnector;
        optional<bool> suppressUnitConversion;
        optional<ssc::LinearTransformation> LinearTransformation;
        optional<ssc::BooleanMappingTransformation> BooleanMappingTransformation;
        optional<ssc::IntegerMappingTransformation> IntegerMappingTransformation;
        optional<ssc::EnumerationMappingTransformation> EnumerationMappingTransformation;
        optional<ssd::ConnectionGeometry> ConnectionGeometry;
        optional<ssc::TAnnotations> Annotations;

        string to_string(void) const;
    };

    class Connections : public IXmlNode
    {
    public:
        vector<Connection> list;

        string to_string(void) const;
    };

    class Connector : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        string name;
        string kind;
        optional<ssc::GTypeReal> Real;
        optional<ssc::GTypeInteger> Integer;
        optional<ssc::GTypeBoolean> Boolean;
        optional<ssc::GTypeString> String;
        optional<ssc::GTypeEnumeration> Enumeration;
        optional<ssc::GTypeBinary> Binary;
        optional<ssd::ConnectorGeometry> ConnectorGeometry;
        optional<ssc::TAnnotations> Annotations;

        string to_string(void) const;
    };

    class TConnectors : public IXmlNode
    {
    public:
        vector<Connector> list;

        string to_string(void) const;
    };

    class TComponent : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        optional<string> name;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> TParameterBindings;
        optional<string> component_type_str;
        optional<ComponentType> component_type;
        string source;
        optional<string> implementation;
        optional<ssc::TAnnotations> Annotations;

        string to_string(void) const;
    };

    class TSignalDictionaryReference : public IXmlNode
    {
    public:
        string dictionary;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> TParameterBindings;
        optional<ssc::TAnnotations> Annotations;

        string to_string(void) const;
    };

    class Elements : public IXmlNode
    {
    public:
        vector<ssd::TComponent> Component;
        vector<ssd::TSignalDictionaryReference> SignalDictionaryReference;
        vector<ssd::TSystem> System;

        string to_string(void) const;
    };

    class TSystem : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        optional<string> name;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> ParameterBindings;
        optional<ssd::Elements> Elements;
        optional<ssd::Connections> Connections;
        optional<ssd::TSignalDictionaries> SignalDictionaries;
        optional<ssd::SystemGeometry> SystemGeometry;
        optional<ssd::GraphicalElements> GraphicalElements;
        optional<ssc::TAnnotations> Annotations;

        string to_string(void) const;
    };

    class SystemStructureDescription : public IXmlNode
    {
    public:
        string version;
        string name;
        optional<string> id;
        optional<string> description;
        optional<string> author;
        optional<string> fileversion;
        optional<string> copyright;
        optional<string> license;
        optional<string> generationTool;
        optional<string> generationDateAndTime;
        ssd::TSystem System;
        optional<ssc::TEnumerations> Enumerations;
        optional<ssc::TUnits> Units;
        optional<ssd::TDefaultExperiment> DefaultExperiment;
        optional<ssc::TAnnotations> Annotations;

        string to_string(void) const;
    };

}
