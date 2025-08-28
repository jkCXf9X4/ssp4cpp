

// This is a generated file, do not alter
// it is based on ssp1_ssd.toml
#pragma once

#include "common_interface.hpp"
#include "common_xml.hpp"

#include "FMI2_Enums.hpp"
#include "SSP1_Enums.hpp"
#include "SSP1_SystemStructureCommon.hpp"
#include "SSP1_SystemStructureParameterMapping.hpp"
#include "SSP1_SystemStructureParameterValues.hpp"

#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::ssp1::ssd
{
    using namespace ssp4cpp::common::interfaces;
    using namespace ssp4cpp::common::xml;
    using namespace std;

    class TSystem;


    class SystemGeometry : public IXmlNode
    {
    public:


        std::string to_string(void) const;
    };

    class ConnectorGeometry : public IXmlNode
    {
    public:


        std::string to_string(void) const;
    };

    class ElementGeometry : public IXmlNode
    {
    public:


        std::string to_string(void) const;
    };

    class ConnectionGeometry : public IXmlNode
    {
    public:


        std::string to_string(void) const;
    };

    class SignalDictionary : public IXmlNode
    {
    public:


        std::string to_string(void) const;
    };

    class TSignalDictionaries : public IXmlNode
    {
    public:
        vector<ssd::SignalDictionary> SignalDictionaries;

        std::string to_string(void) const;
    };

    class ParameterMapping : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        optional<string> type;
        optional<string> source;
        optional<string> sourceBase;
        optional<ssm::ParameterMapping> ParameterMapping;

        std::string to_string(void) const;
    };

    class ParameterBinding : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        optional<string> type;
        optional<string> source;
        optional<string> sourceBase;
        optional<string> prefix;
        optional<ssv::ParameterSet> ParameterValues;
        optional<ssd::ParameterMapping> ParameterMapping;

        std::string to_string(void) const;
    };

    class TParameterBindings : public IXmlNode
    {
    public:
        vector<ssd::ParameterBinding> ParameterBindings;

        std::string to_string(void) const;
    };

    class GraphicalElements : public IXmlNode
    {
    public:


        std::string to_string(void) const;
    };

    class TDefaultExperiment : public IXmlNode
    {
    public:
        optional<double> startTime;
        optional<double> stopTime;
        optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
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

        std::string to_string(void) const;
    };

    class Connections : public IXmlNode
    {
    public:
        vector<ssd::Connection> Connections;

        std::string to_string(void) const;
    };

    class Connector : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        string name;
        fmi2::md::Causality kind;
        optional<ssc::GTypeReal> Real;
        optional<ssc::GTypeInteger> Integer;
        optional<ssc::GTypeBoolean> Boolean;
        optional<ssc::GTypeString> String;
        optional<ssc::GTypeEnumeration> Enumeration;
        optional<ssc::GTypeBinary> Binary;
        optional<ssd::ConnectorGeometry> ConnectorGeometry;
        optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
    };

    class TConnectors : public IXmlNode
    {
    public:
        vector<ssd::Connector> Connectors;

        std::string to_string(void) const;
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
        optional<ssd::ComponentType> type;
        string source;
        optional<string> implementation;
        optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
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

        std::string to_string(void) const;
    };

    class Elements : public IXmlNode
    {
    public:
        vector<ssd::TComponent> Components;
        vector<ssd::TSignalDictionaryReference> SignalDictionaryReferences;
        vector<ssd::TSystem> Systems;

        std::string to_string(void) const;
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

        std::string to_string(void) const;
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

        std::string to_string(void) const;
    };

}
