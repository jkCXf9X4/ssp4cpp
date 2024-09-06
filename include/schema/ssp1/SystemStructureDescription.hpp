#pragma once

#include <string>
#include <vector>
#include <optional>

#include "SystemStructureCommon.hpp"

namespace ssp4cpp::ssp1::ssd
{
    using namespace std;
    using namespace ssp4cpp::ssp1;

    struct TSystem;

    // Enum for ComponentKind
    enum class ComponentKind
    {
        XFmuSharedlibrary,
        XSspDefinition,
        XSspPackage
    };

    // Geometry related structs
    typedef struct
    {
    } SystemGeometry;

    typedef struct
    {
    } ConnectorGeometry;

    typedef struct
    {
    } ElementGeometry;

    typedef struct
    {
    } ConnectionGeometry;

    typedef struct
    {
    } TSignalDictionaries;

    typedef struct
    {
    } TParameterBindings;

    typedef struct
    {
    } GraphicalElements;

    typedef struct
    {
    } TDefaultExperiment;

    typedef struct
    {
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
    } Connection;

    typedef struct
    {
        vector<Connection> list;
    } Connections;

    typedef struct
    {
        // ABaseElement
        optional<string> id;
        optional<string> description;

        string name;
        string kind;

        // ssc:GTypeChoice
        optional<ssc::GTypeReal> Real;
        optional<ssc::GTypeInteger> Integer;
        optional<ssc::GTypeBoolean> Boolean;
        optional<ssc::GTypeString> String;
        optional<ssc::GTypeEnumeration> Enumeration;
        optional<ssc::GTypeBinary> Binary;

        optional<ssd::ConnectorGeometry> ConnectorGeometry;
        optional<ssc::TAnnotations> Annotations;
    } Connector;

    typedef struct
    {
        vector<Connector> list;
    } TConnectors;

    typedef struct
    {
        // TElement
        // - ABaseElement
        optional<string> id;
        optional<string> description;

        // TElement cont
        optional<string> name;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> TParameterBindings;

        optional<ssd::ComponentKind> component_type;
        string source;
        optional<string> implementation;
        optional<ssc::TAnnotations> Annotations;
    } TComponent;

    typedef struct
    {
        string dictionary;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> TParameterBindings;
        optional<ssc::TAnnotations> Annotations;
    } TSignalDictionaryReference;

    typedef struct
    {
        vector<ssd::TComponent> Components;
        vector<ssd::TSignalDictionaryReference> SignalDictionaryReferences;
        vector<ssd::TSystem> Systems;
    } Elements;

    typedef struct TSystem
    {
        // TElement
        // - ABaseElement
        optional<string> id;
        optional<string> description;

        // TElement cont
        optional<string> name;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> ParameterBindings;

        // TSystem cont
        optional<ssd::Elements> Elements;
        optional<ssd::Connections> Connections;
        optional<ssd::TSignalDictionaries> SignalDictionaries;
        optional<ssd::SystemGeometry> SystemGeometry;
        optional<ssd::GraphicalElements> GraphicalElements;
        optional<ssc::TAnnotations> Annotations;
    } TSystem;

    typedef struct
    {
        string version;
        string name;

        // ABaseElement
        optional<string> id;
        optional<string> description;

        // ATOPLevelMetaData
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
    } SystemStructureDescription;

}