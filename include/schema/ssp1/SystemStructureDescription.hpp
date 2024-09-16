

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

    // // Forward declarations
    // struct TSystem;
    // std::ostream &operator<<(std::ostream &os, const TSystem &sys);

    // Forward declarations
    struct TSystem;
    std::ostream &operator<<(std::ostream &os, const TSystem &sys);

    // Declarations

    // Geometry related structes
    struct SystemGeometry
    {
        friend ostream &operator<<(ostream &os, const SystemGeometry &obj)
        {
            os << "SystemGeometry()" << endl;
            return os;
        }
    };

    struct ConnectorGeometry
    {
        friend ostream &operator<<(ostream &os, const ConnectorGeometry &obj)
        {
            os << "ConnectorGeometry()" << endl;
            return os;
        }
    };

    struct ElementGeometry
    {
        friend ostream &operator<<(ostream &os, const ElementGeometry &obj)
        {
            os << "ElementGeometry()" << endl;
            return os;
        }
    };

    struct ConnectionGeometry
    {
        friend ostream &operator<<(ostream &os, const ConnectionGeometry &obj)
        {
            os << "ConnectionGeometry()" << endl;
            return os;
        }
    };

    struct TSignalDictionaries
    {
        friend ostream &operator<<(ostream &os, const TSignalDictionaries &obj)
        {
            os << "TSignalDictionaries()" << endl;
            return os;
        }
    };

    struct TParameterBindings
    {
        friend ostream &operator<<(ostream &os, const TParameterBindings &obj)
        {
            os << "TParameterBindings()" << endl;
            return os;
        }
    };

    struct GraphicalElements
    {
        friend ostream &operator<<(ostream &os, const GraphicalElements &obj)
        {
            os << "GraphicalElements()" << endl;
            return os;
        }
    };

    struct TDefaultExperiment
    {
        friend ostream &operator<<(ostream &os, const TDefaultExperiment &obj)
        {
            os << "TDefaultExperiment()" << endl;
            return os;
        }
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

        friend std::ostream &operator<<(std::ostream &os, const Connection &conn)
        {
            os << "Connection {\n"
               << "startElement: " << print_optional(conn.startElement)
               << "startConnector: " << conn.startConnector << endl
               << "endElement: " << print_optional(conn.endElement)
               << "endConnector: " << conn.endConnector << endl
               << "suppressUnitConversion: " << print_optional(conn.suppressUnitConversion)
               << "LinearTransformation: " << print_optional(conn.LinearTransformation)
               << "BooleanMappingTransformation: " << print_optional(conn.BooleanMappingTransformation)
               << "IntegerMappingTransformation: " << print_optional(conn.IntegerMappingTransformation)
               << "EnumerationMappingTransformation: " << print_optional(conn.EnumerationMappingTransformation)
               << "ConnectionGeometry: " << print_optional(conn.ConnectionGeometry)
               << "Annotations: " << print_optional(conn.Annotations)
               << " }" << endl;
            return os;
        }
    };

    struct Connections
    {
    
        vector<Connection> list;

        friend std::ostream &operator<<(std::ostream &os, const Connections &conns)
        {
            os << "Connections { \n";
            for (const auto &conn : conns.list)
            {
                os << conn << endl;
            }
            os << " }" << endl;
            return os;
        }
    };

    struct Connector
    {
    
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

        friend std::ostream &operator<<(std::ostream &os, const Connector &conn)
        {
            os << "Connector {\n"
               << "id: " << print_optional(conn.id)
               << "description: " << print_optional(conn.description)
               << "name: " << conn.name << endl
               << "kind: " << conn.kind << endl
               << "Real: " << print_optional(conn.Real)
               << "Integer: " << print_optional(conn.Integer)
               << "Boolean: " << print_optional(conn.Boolean)
               << "String: " << print_optional(conn.String)
               << "Enumeration: " << print_optional(conn.Enumeration)
               << "Binary: " << print_optional(conn.Binary)
               << "ConnectorGeometry: " << print_optional(conn.ConnectorGeometry)
               << "Annotations: " << print_optional(conn.Annotations)
               << " }" << endl;
            return os;
        }
    };

    struct TConnectors
    {
    
        vector<Connector> list;

        friend std::ostream &operator<<(std::ostream &os, const TConnectors &conns)
        {
            os << "TConnectors {\n";
            for (const auto &conn : conns.list)
            {
                os << conn << endl;
            }
            os << " }" << endl;
            return os;
        }
    };

    struct TComponent
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

        optional<string> component_type;
        string source;
        optional<string> implementation;
        optional<ssc::TAnnotations> Annotations;

        friend std::ostream &operator<<(std::ostream &os, const TComponent &comp)
        {
            os << "TComponent {\n"
               << "id: " << print_optional(comp.id)
               << "description: " << print_optional(comp.description)
               << "name: " << print_optional(comp.name)
               << "Connectors: " << print_optional(comp.Connectors)
               << "ElementGeometry: " << print_optional(comp.ElementGeometry)
               << "TParameterBindings: " << print_optional(comp.TParameterBindings)
               << "component_type: " << print_optional(comp.component_type)
               << "source: " << comp.source << endl
               << "implementation: " << print_optional(comp.implementation)
               << "Annotations: " << print_optional(comp.Annotations)
               << " }" << endl;
            return os;
        }
    };

    struct TSignalDictionaryReference
    {
    
        string dictionary;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> TParameterBindings;
        optional<ssc::TAnnotations> Annotations;

        friend std::ostream &operator<<(std::ostream &os, const TSignalDictionaryReference &ref)
        {
            os << "TSignalDictionaryReference {\n"
               << "dictionary: " << ref.dictionary << endl
               << "Connectors: " << print_optional(ref.Connectors)
               << "ElementGeometry: " << print_optional(ref.ElementGeometry)
               << "TParameterBindings: " << print_optional(ref.TParameterBindings)
               << "Annotations: " << print_optional(ref.Annotations)
               << " }" << endl;
            return os;
        }
    };

    struct Elements
    {
    
        vector<ssd::TComponent> components;
        vector<ssd::TSignalDictionaryReference> signal_dictionary_references;
        vector<ssd::TSystem> systems;

        friend std::ostream &operator<<(std::ostream &os, const Elements &elems)
        {
            os << "Elements {\ncomponents {\n";
            for (const auto &comp : elems.components)
            {
                os << comp << endl;
            }
            os << "} \nsignal_dictionary_references {\n";
            for (const auto &ref : elems.signal_dictionary_references)
            {
                os << ref << endl;
            }
            os << "} \nsystems {\n";
            for (const auto &sys : elems.systems)
            {
                os << sys << endl;
            }
            os << "}\n}\n";
            return os;
        }
    };

    struct TSystem
    {
    
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

        friend std::ostream &operator<<(std::ostream &os, const TSystem &sys)
        {
            os << "TSystem {\n"
               << "id: " << print_optional(sys.id)
               << "description: " << print_optional(sys.description)
               << "name: " << print_optional(sys.name)
               << "Connectors: " << print_optional(sys.Connectors)
               << "ElementGeometry: " << print_optional(sys.ElementGeometry)
               << "ParameterBindings: " << print_optional(sys.ParameterBindings)
               << "Elements: " << print_optional(sys.Elements)
               << "Connections: " << print_optional(sys.Connections)
               << "SignalDictionaries: " << print_optional(sys.SignalDictionaries)
               << "SystemGeometry: " << print_optional(sys.SystemGeometry)
               << "GraphicalElements: " << print_optional(sys.GraphicalElements)
               << "Annotations: " << print_optional(sys.Annotations)
               << " }\n";
            return os;
        }
    };

    struct SystemStructureDescription
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

        friend std::ostream &operator<<(std::ostream &os, const SystemStructureDescription &ssd)
        {
            os << "SystemStructureDescription {\n"
               << "version: " << ssd.version << endl
               << "name: " << ssd.name << endl
               << "id: " << print_optional(ssd.id)
               << "description: " << print_optional(ssd.description)
               << "author: " << print_optional(ssd.author)
               << "fileversion: " << print_optional(ssd.fileversion)
               << "copyright: " << print_optional(ssd.copyright)
               << "license: " << print_optional(ssd.license)
               << "generationTool: " << print_optional(ssd.generationTool)
               << "generationDateAndTime: " << print_optional(ssd.generationDateAndTime)
               << "System: " << endl
               << ssd.System << endl
               << "Enumerations: " << print_optional(ssd.Enumerations)
               << "Units: " << print_optional(ssd.Units)
               << "DefaultExperiment: " << print_optional(ssd.DefaultExperiment)
               << "Annotations: " << print_optional(ssd.Annotations)
               << " }\n";
            return os;
        }
    };
}