#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "SystemStructureCommon.hpp"

namespace ssp4cpp::ssp1::ssd
{
    using namespace std;
    using namespace ssp4cpp::ssp1;

    // Forward declarations
    struct TSystem;

    // Declarations

    // Geometry related structures
    struct SystemGeometry
    {
    };
    string to_string(const SystemGeometry &obj);

    struct ConnectorGeometry
    {
    };
    string to_string(const ConnectorGeometry &obj);

    struct ElementGeometry
    {
    };
    string to_string(const ElementGeometry &obj);

    struct ConnectionGeometry
    {
    };
    string to_string(const ConnectionGeometry &obj);

    struct TSignalDictionaries
    {
    };
    string to_string(const TSignalDictionaries &obj);

    struct TParameterBindings
    {
    };
    string to_string(const TParameterBindings &obj);

    struct GraphicalElements
    {
    };
    string to_string(const GraphicalElements &obj);

    struct TDefaultExperiment
    {
    };
    string to_string(const TDefaultExperiment &obj);

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
    string to_string(const Connection &conn);

    struct Connections
    {
        vector<Connection> list;
    };
    string to_string(const Connections &conns);

    struct Connector
    {
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
    };
    string to_string(const Connector &conn);

    struct TConnectors
    {
        vector<Connector> list;
    };
    string to_string(const TConnectors &conns);

    struct TComponent
    {
        optional<string> id;
        optional<string> description;
        optional<string> name;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> TParameterBindings;
        optional<string> component_type;
        string source;
        optional<string> implementation;
        optional<ssc::TAnnotations> Annotations;
    };
    string to_string(const TComponent &comp);

    struct TSignalDictionaryReference
    {
        string dictionary;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> TParameterBindings;
        optional<ssc::TAnnotations> Annotations;
    };
    string to_string(const TSignalDictionaryReference &ref);

    struct Elements
    {
        vector<ssd::TComponent> components;
        vector<ssd::TSignalDictionaryReference> signal_dictionary_references;
        vector<ssd::TSystem> systems;
    };
    string to_string(const Elements &elems);

    struct TSystem
    {
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
    };
    string to_string(const TSystem &sys);

    struct SystemStructureDescription
    {
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
    };
    string to_string(const SystemStructureDescription &ssd);
}