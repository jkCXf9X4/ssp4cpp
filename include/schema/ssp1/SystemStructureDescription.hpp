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


    class SignalDictionary : public IXmlNode
    {
    public:


        string to_string(void) const;
    };


    class TSignalDictionaries : public IXmlNode
    {
    public:
        vector<ssd::SignalDictionary> SignalDictionaries;

        string to_string(void) const;
    };


    class ParameterBinding : public IXmlNode
    {
    public:


        string to_string(void) const;
    };


    class TParameterBindings : public IXmlNode
    {
    public:
        vector<ssd::ParameterBinding> ParameterBindings;

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
        optional<double> startTime;
        optional<double> stopTime;
        optional<ssc::TAnnotations> Annotations;

        string to_string(void) const;
    };


    class Connection : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
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
        vector<ssd::Connection> Connections;

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
        vector<ssd::Connector> Connectors;

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
        optional<ssd::TParameterBindings> ParameterBindings;
        optional<string> type;
        string source;
        optional<string> implementation;
        optional<ssc::TAnnotations> Annotations;

        string to_string(void) const;
    };


    class TSignalDictionaryReference : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        optional<string> name;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> ParameterBindings;
        string dictionary;
        optional<ssc::TAnnotations> Annotations;

        string to_string(void) const;
    };


    class Elements : public IXmlNode
    {
    public:
        vector<ssd::TComponent> Components;
        vector<ssd::TSignalDictionaryReference> SignalDictionaryReferences;
        vector<ssd::TSystem> Systems;

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
