

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
    };

    struct Connections
    {
        vector<Connection> list;
    };

    struct Connector
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
    };

    struct TConnectors
    {
        vector<Connector> list;
    };

    struct TComponent
    {
        // TElement
        // - ABaseElement
        optional<string> id;
        optional<string> description;

        // TElement cont
        optional<string> name;
        vector<ssd::TConnectors> Connectors;
        vector<ssd::ElementGeometry> ElementGeometry;
        vector<ssd::TParameterBindings> TParameterBindings;

        optional<ssd::ComponentKind> component_type;
        string source;
        optional<string> implementation;
        optional<ssc::TAnnotations> Annotations;
    };

    // Other related structs
    struct TSignalDictionaryReference
    {
        string dictionary;
        vector<ssd::TConnectors> Connectors;
        vector<ssd::ElementGeometry> ElementGeometry;
        vector<ssd::TParameterBindings> TParameterBindings;
        optional<ssc::TAnnotations> Annotations;
    };

    struct Elements
    {
        vector<ssd::TComponent> Components;
        vector<ssd::TSignalDictionaryReference> SignalDictionaryReferences;
        vector<ssd::TSystem> Systems;
    };

    struct TSystem
    {
        // TElement
        // - ABaseElement
        optional<string> id;
        optional<string> description;

        // TElement cont
        optional<string> name;
        vector<ssd::TConnectors> Connectors;
        vector<ssd::ElementGeometry> ElementGeometry;
        vector<ssd::TParameterBindings> TParameterBindings;

        // TSystem cont
        optional<ssd::Elements> Elements;
        optional<ssd::Connections> Connections;
        optional<ssd::TSignalDictionaries> SignalDictionaries;
        optional<ssd::SystemGeometry> SystemGeometry;
        optional<ssd::GraphicalElements> GraphicalElements;
        optional<ssc::TAnnotations> Annotations;
    };

    // Struct declarations
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

        TSystem *System;
        optional<ssc::TEnumerations> Enumerations;
        optional<ssc::TUnits> Units;
        optional<ssd::TDefaultExperiment> DefaultExperiment;
        optional<ssc::TAnnotations> Annotations;
    } SystemStructureDescription;

    ostream& operator<<(ostream& os, const ssd::SystemStructureDescription& book) {
    return os << "SSD:\nversion: " << book.version << endl
              << "name: " << book.name << endl
              << "id: " << book.id << endl
              << "description:" << book.description << endl;
}
}
