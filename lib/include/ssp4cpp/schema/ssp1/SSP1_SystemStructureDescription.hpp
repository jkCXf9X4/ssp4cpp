

// This is a generated file, do not alter
// it is based on ssp1_ssd.toml
#pragma once

#include "ssp4cpp/utils/interface.hpp"

#include "ssp4cpp/schema/fmi2/FMI2_Enums.hpp"
#include "ssp4cpp/schema/ssp1/SSP1_Enums.hpp"
#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureCommon.hpp"
#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureParameterMapping.hpp"
#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureParameterValues.hpp"

#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::ssp1::ssd
{
    using namespace utils::interfaces;

    class TSystem;




    class SystemGeometry : public IXmlNode
    {
    public:


        std::string to_string(void) const override;
    };

    class ConnectorGeometry : public IXmlNode
    {
    public:


        std::string to_string(void) const override;
    };

    class ElementGeometry : public IXmlNode
    {
    public:


        std::string to_string(void) const override;
    };

    class ConnectionGeometry : public IXmlNode
    {
    public:


        std::string to_string(void) const override;
    };

    class SignalDictionary : public IXmlNode
    {
    public:


        std::string to_string(void) const override;
    };

    class TSignalDictionaries : public IXmlNode
    {
    public:
        std::vector<ssd::SignalDictionary> SignalDictionaries;

        std::string to_string(void) const override;
    };

    class ParameterMapping : public IXmlNode
    {
    public:
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::optional<std::string> type;
        std::optional<std::string> source;
        std::optional<std::string> sourceBase;
        std::optional<ssm::ParameterMapping> ParameterMapping;

        std::string to_string(void) const override;
    };

    class ParameterBinding : public IXmlNode
    {
    public:
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::optional<std::string> type;
        std::optional<std::string> source;
        std::optional<std::string> sourceBase;
        std::optional<std::string> prefix;
        std::optional<ssv::ParameterSet> ParameterValues;
        std::optional<ssd::ParameterMapping> ParameterMapping;

        std::string to_string(void) const override;
    };

    class TParameterBindings : public IXmlNode
    {
    public:
        std::vector<ssd::ParameterBinding> ParameterBindings;

        std::string to_string(void) const override;
    };

    class GraphicalElements : public IXmlNode
    {
    public:


        std::string to_string(void) const override;
    };

    class TDefaultExperiment : public IXmlNode
    {
    public:
        std::optional<double> startTime;
        std::optional<double> stopTime;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const override;
    };

    class Connection : public IXmlNode
    {
    public:
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::optional<std::string> startElement;
        std::string startConnector;
        std::optional<std::string> endElement;
        std::string endConnector;
        std::optional<bool> suppressUnitConversion;
        std::optional<ssc::LinearTransformation> LinearTransformation;
        std::optional<ssc::BooleanMappingTransformation> BooleanMappingTransformation;
        std::optional<ssc::IntegerMappingTransformation> IntegerMappingTransformation;
        std::optional<ssc::EnumerationMappingTransformation> EnumerationMappingTransformation;
        std::optional<ssd::ConnectionGeometry> ConnectionGeometry;
        std::optional<ssc::TAnnotations> Annotations;
        std::optional<double> information_delay;

        std::string to_string(void) const override;
    };

    class Connections : public IXmlNode
    {
    public:
        std::vector<ssd::Connection> Connections;

        std::string to_string(void) const override;
    };

    class Connector : public IXmlNode
    {
    public:
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::string name;
        fmi2::md::Causality kind;
        std::optional<ssc::GTypeReal> Real;
        std::optional<ssc::GTypeInteger> Integer;
        std::optional<ssc::GTypeBoolean> Boolean;
        std::optional<ssc::GTypeString> String;
        std::optional<ssc::GTypeEnumeration> Enumeration;
        std::optional<ssc::GTypeBinary> Binary;
        std::optional<ssd::ConnectorGeometry> ConnectorGeometry;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const override;
    };

    class TConnectors : public IXmlNode
    {
    public:
        std::vector<ssd::Connector> Connectors;

        std::string to_string(void) const override;
    };

    class TComponent : public IXmlNode
    {
    public:
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::optional<std::string> name;
        std::optional<ssd::TConnectors> Connectors;
        std::optional<ssd::ElementGeometry> ElementGeometry;
        std::optional<ssd::TParameterBindings> ParameterBindings;
        std::optional<ssd::ComponentType> type;
        std::string source;
        std::optional<std::string> implementation;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const override;
    };

    class TSignalDictionaryReference : public IXmlNode
    {
    public:
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::optional<std::string> name;
        std::optional<ssd::TConnectors> Connectors;
        std::optional<ssd::ElementGeometry> ElementGeometry;
        std::optional<ssd::TParameterBindings> ParameterBindings;
        std::string dictionary;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const override;
    };

    class Elements : public IXmlNode
    {
    public:
        std::vector<ssd::TComponent> Components;
        std::vector<ssd::TSignalDictionaryReference> SignalDictionaryReferences;
        std::vector<ssd::TSystem> Systems;

        std::string to_string(void) const override;
    };

    class TSystem : public IXmlNode
    {
    public:
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::optional<std::string> name;
        std::optional<ssd::TConnectors> Connectors;
        std::optional<ssd::ElementGeometry> ElementGeometry;
        std::optional<ssd::TParameterBindings> ParameterBindings;
        std::optional<ssd::Elements> Elements;
        std::optional<ssd::Connections> Connections;
        std::optional<ssd::TSignalDictionaries> SignalDictionaries;
        std::optional<ssd::SystemGeometry> SystemGeometry;
        std::optional<ssd::GraphicalElements> GraphicalElements;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const override;
    };

    class SystemStructureDescription : public IXmlNode
    {
    public:
        std::string version;
        std::string name;
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::optional<std::string> author;
        std::optional<std::string> fileversion;
        std::optional<std::string> copyright;
        std::optional<std::string> license;
        std::optional<std::string> generationTool;
        std::optional<std::string> generationDateAndTime;
        ssd::TSystem System;
        std::optional<ssc::TEnumerations> Enumerations;
        std::optional<ssc::TUnits> Units;
        std::optional<ssd::TDefaultExperiment> DefaultExperiment;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const override;
    };

}
