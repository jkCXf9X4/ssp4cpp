#pragma once

#include <string>
#include <vector>
#include <optional>

#include "SystemStructureCommon.hpp"

namespace ssd
{
    struct TSystem;

    // Enum for ComponentKind
    enum class ComponentKind
    {
        XFmuSharedlibrary,
        XSspDefinition,
        XSspPackage
    };

    // Geometry related structs
    struct SystemGeometry
    {
    };
    struct ConnectorGeometry
    {
    };
    struct ElementGeometry
    {
    };
    struct ConnectionGeometry
    {
    };

    struct TSignalDictionaries
    {
    };
    struct TParameterBindings
    {
    };
    struct GraphicalElements
    {
    };
    struct TDefaultExperiment
    {
    };

    struct Connection
    {
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
    };

    struct Connections
    {
        std::vector<Connection> list;
    };

    struct Connector
    {
        // ABaseElement
        std::optional<std::string> id;
        std::optional<std::string> description;

        std::string name;
        std::string kind;

        // ssc:GTypeChoice
        std::optional<ssc::GTypeReal> Real;
        std::optional<ssc::GTypeInteger> Integer;
        std::optional<ssc::GTypeBoolean> Boolean;
        std::optional<ssc::GTypeString> String;
        std::optional<ssc::GTypeEnumeration> Enumeration;
        std::optional<ssc::GTypeBinary> Binary;

        std::optional<ssd::ConnectorGeometry> ConnectorGeometry;
        std::optional<ssc::TAnnotations> Annotations;
    };

    struct TConnectors
    {
        std::vector<Connector> list;
    };

    struct TComponent
    {
        // TElement
        // - ABaseElement
        std::optional<std::string> id;
        std::optional<std::string> description;

        // TElement cont
        std::optional<std::string> name;
        std::vector<ssd::TConnectors> Connectors;
        std::vector<ssd::ElementGeometry> ElementGeometry;
        std::vector<ssd::TParameterBindings> TParameterBindings;

        std::optional<ssd::ComponentKind> component_type;
        std::string source;
        std::optional<std::string> implementation;
        std::optional<ssc::TAnnotations> Annotations;
    };

    // Other related structs
    struct TSignalDictionaryReference
    {
        std::string dictionary;
        std::vector<ssd::TConnectors> Connectors;
        std::vector<ssd::ElementGeometry> ElementGeometry;
        std::vector<ssd::TParameterBindings> TParameterBindings;
        std::optional<ssc::TAnnotations> Annotations;
    };

    struct Elements
    {
        std::vector<ssd::TComponent> Components;
        std::vector<ssd::TSignalDictionaryReference> SignalDictionaryReferences;
        std::vector<ssd::TSystem> Systems;
    };

    struct TSystem
    {
        // TElement
        // - ABaseElement
        std::optional<std::string> id;
        std::optional<std::string> description;

        // TElement cont
        std::optional<std::string> name;
        std::vector<ssd::TConnectors> Connectors;
        std::vector<ssd::ElementGeometry> ElementGeometry;
        std::vector<ssd::TParameterBindings> TParameterBindings;

        // TSystem cont
        std::optional<ssd::Elements> Elements;
        std::optional<ssd::Connections> Connections;
        std::optional<ssd::TSignalDictionaries> SignalDictionaries;
        std::optional<ssd::SystemGeometry> SystemGeometry;
        std::optional<ssd::GraphicalElements> GraphicalElements;
        std::optional<ssc::TAnnotations> Annotations;
    };

    // Struct declarations
    struct SystemStructureDescription
    {
        std::string version;
        std::string name;

        // ABaseElement
        std::optional<std::string> id;
        std::optional<std::string> description;

        // ATOPLevelMetaData
        std::optional<std::string> author;
        std::optional<std::string> fileversion;
        std::optional<std::string> copyright;
        std::optional<std::string> license;
        std::optional<std::string> generationTool;
        std::optional<std::string> generationDateAndTime;

        TSystem *System;
        std::optional<ssc::TEnumerations> Enumerations;
        std::optional<ssc::TUnits> Units;
        std::optional<ssd::TDefaultExperiment> DefaultExperiment;
        std::optional<ssc::TAnnotations> Annotations;
    };
}