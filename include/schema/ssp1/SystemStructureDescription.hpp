

#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <sstream>

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

    class SystemGeometry;
    std::ostream &operator<<(std::ostream &os, const SystemGeometry &obj);

    class ConnectorGeometry;
    std::ostream &operator<<(std::ostream &os, const ConnectorGeometry &obj);

    class ElementGeometry;
    std::ostream &operator<<(std::ostream &os, const ElementGeometry &obj);

    class ConnectionGeometry;
    std::ostream &operator<<(std::ostream &os, const ConnectionGeometry &obj);

    class TSignalDictionaries;
    std::ostream &operator<<(std::ostream &os, const TSignalDictionaries &obj);

    class TParameterBindings;
    std::ostream &operator<<(std::ostream &os, const TParameterBindings &obj);

    class GraphicalElements;
    std::ostream &operator<<(std::ostream &os, const GraphicalElements &obj);

    class TDefaultExperiment;
    std::ostream &operator<<(std::ostream &os, const TDefaultExperiment &obj);

    class Connection;
    std::ostream &operator<<(std::ostream &os, const Connection &conn);

    class Connections;
    std::ostream &operator<<(std::ostream &os, const Connections &conns);

    class Connector;
    std::ostream &operator<<(std::ostream &os, const Connector &conn);

    class TConnectors;
    std::ostream &operator<<(std::ostream &os, const TConnectors &conns);

    class TComponent;
    std::ostream &operator<<(std::ostream &os, const TComponent &comp);

    class TSignalDictionaryReference;
    std::ostream &operator<<(std::ostream &os, const TSignalDictionaryReference &ref);

    class Elements;
    std::ostream &operator<<(std::ostream &os, const Elements &elems);

    class SystemStructureDescription;
    std::ostream &operator<<(std::ostream &os, const SystemStructureDescription &ssd);

    // Templates
    template <typename T>
    stringstream print_optional(const optional<T> &opt)
    {
        stringstream ss;
        if (opt)
        {
            ss << *opt << endl;
        }
        else
        {
            ss << "null" << endl;
        }
        return ss;
    }

    // Declarations

    // Enum for ComponentKind
    enum class ComponentKind
    {
        XFmuSharedlibrary,
        XSspDefinition,
        XSspPackage
    };

    // std::ostream &operator<<(std::ostream &os, const ComponentKind &kind)
    // {
    //     switch (kind)
    //     {
    //     case ComponentKind::XFmuSharedlibrary:
    //         os << "XFmuSharedlibrary";
    //         break;
    //     case ComponentKind::XSspDefinition:
    //         os << "XSspDefinition";
    //         break;
    //     case ComponentKind::XSspPackage:
    //         os << "XSspPackage";
    //         break;
    //     }
    //     return os;
    // }

    // Geometry related classes
    class SystemGeometry
    {
        friend ostream &operator<<(ostream &os, const SystemGeometry &obj)
        {
            os << "SystemGeometry()" << endl;
            return os;
        }
    };

    class ConnectorGeometry
    {
        friend ostream &operator<<(ostream &os, const ConnectorGeometry &obj)
        {
            os << "ConnectorGeometry()" << endl;
            return os;
        }
    };

    class ElementGeometry
    {
        friend ostream &operator<<(ostream &os, const ElementGeometry &obj)
        {
            os << "ElementGeometry()" << endl;
            return os;
        }
    };

    class ConnectionGeometry
    {
        friend ostream &operator<<(ostream &os, const ConnectionGeometry &obj)
        {
            os << "ConnectionGeometry()" << endl;
            return os;
        }
    };

    class TSignalDictionaries
    {
        friend ostream &operator<<(ostream &os, const TSignalDictionaries &obj)
        {
            os << "TSignalDictionaries()" << endl;
            return os;
        }
    };

    class TParameterBindings
    {
        friend ostream &operator<<(ostream &os, const TParameterBindings &obj)
        {
            os << "TParameterBindings()" << endl;
            return os;
        }
    };

    class GraphicalElements
    {
        friend ostream &operator<<(ostream &os, const GraphicalElements &obj)
        {
            os << "GraphicalElements()" << endl;
            return os;
        }
    };

    class TDefaultExperiment
    {
        friend ostream &operator<<(ostream &os, const TDefaultExperiment &obj)
        {
            os << "TDefaultExperiment()" << endl;
            return os;
        }
    };

    class Connection
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

        friend std::ostream &operator<<(std::ostream &os, const Connection &conn)
        {
            os << "Connection {\n"
               << "startElement: " << print_optional(conn.startElement).str()
               << "startConnector: " << conn.startConnector << endl
               << "endElement: " << print_optional(conn.endElement).str()
               << "endConnector: " << conn.endConnector << endl
               << "suppressUnitConversion: " << print_optional(conn.suppressUnitConversion).str()
               << "LinearTransformation: " << print_optional(conn.LinearTransformation).str()
               << "BooleanMappingTransformation: " << print_optional(conn.BooleanMappingTransformation).str()
               << "IntegerMappingTransformation: " << print_optional(conn.IntegerMappingTransformation).str()
               << "EnumerationMappingTransformation: " << print_optional(conn.EnumerationMappingTransformation).str()
               << "ConnectionGeometry: " << print_optional(conn.ConnectionGeometry).str()
               << "Annotations: " << print_optional(conn.Annotations).str()
               << " }" << endl;
            return os;
        }
    };

    class Connections
    {
    public:
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

    class Connector
    {
    public:
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
               << "id: " << print_optional(conn.id).str()
               << "description: " << print_optional(conn.description).str()
               << "name: " << conn.name << endl
               << "kind: " << conn.kind << endl
               << "Real: " << print_optional(conn.Real).str()
               << "Integer: " << print_optional(conn.Integer).str()
               << "Boolean: " << print_optional(conn.Boolean).str()
               << "String: " << print_optional(conn.String).str()
               << "Enumeration: " << print_optional(conn.Enumeration).str()
               << "Binary: " << print_optional(conn.Binary).str()
               << "ConnectorGeometry: " << print_optional(conn.ConnectorGeometry).str()
               << "Annotations: " << print_optional(conn.Annotations).str()
               << " }" << endl;
            return os;
        }
    };

    class TConnectors
    {
    public:
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

    class TComponent
    {
    public:
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

        friend std::ostream &operator<<(std::ostream &os, const TComponent &comp)
        {
            os << "TComponent {\n"
               << "id: " << print_optional(comp.id).str()
               << "description: " << print_optional(comp.description).str()
               << "name: " << print_optional(comp.name).str()
               << "Connectors: " << print_optional(comp.Connectors).str()
               << "ElementGeometry: " << print_optional(comp.ElementGeometry).str()
               << "TParameterBindings: " << print_optional(comp.TParameterBindings).str()
            //    << "component_type: " << print_optional(comp.component_type)
               << "source: " << comp.source << endl
               << "implementation: " << print_optional(comp.implementation).str()
               << "Annotations: " << print_optional(comp.Annotations).str()
               << " }" << endl;
            return os;
        }
    };

    class TSignalDictionaryReference
    {
    public:
        string dictionary;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> TParameterBindings;
        optional<ssc::TAnnotations> Annotations;

        friend std::ostream &operator<<(std::ostream &os, const TSignalDictionaryReference &ref)
        {
            os << "TSignalDictionaryReference {\n"
               << "dictionary: " << ref.dictionary << endl
               << "Connectors: " << print_optional(ref.Connectors).str()
               << "ElementGeometry: " << print_optional(ref.ElementGeometry).str()
               << "TParameterBindings: " << print_optional(ref.TParameterBindings).str()
               << "Annotations: " << print_optional(ref.Annotations).str()
               << " }" << endl;
            return os;
        }
    };

    class Elements
    {
    public:
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
            os << "} \nignal_dictionary_references {\n";
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

    class TSystem
    {
    public:
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
               << "id: " << print_optional(sys.id).str()
               << "description: " << print_optional(sys.description).str()
               << "name: " << print_optional(sys.name).str()
               << "Connectors: " << print_optional(sys.Connectors).str()
               << "ElementGeometry: " << print_optional(sys.ElementGeometry).str()
               << "ParameterBindings: " << print_optional(sys.ParameterBindings).str()
               << "Elements: " << print_optional(sys.Elements).str()
               << "Connections: " << print_optional(sys.Connections).str()
               << "SignalDictionaries: " << print_optional(sys.SignalDictionaries).str()
               << "SystemGeometry: " << print_optional(sys.SystemGeometry).str()
               << "GraphicalElements: " << print_optional(sys.GraphicalElements).str()
               << "Annotations: " << print_optional(sys.Annotations).str()
               << " }\n";
            return os;
        }
    };

    class SystemStructureDescription
    {
    public:
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
               << "id: " << print_optional(ssd.id).str()
               << "description: " << print_optional(ssd.description).str()
               << "author: " << print_optional(ssd.author).str()
               << "fileversion: " << print_optional(ssd.fileversion).str()
               << "copyright: " << print_optional(ssd.copyright).str()
               << "license: " << print_optional(ssd.license).str()
               << "generationTool: " << print_optional(ssd.generationTool).str()
               << "generationDateAndTime: " << print_optional(ssd.generationDateAndTime).str()
               << "System: " << endl
               << ssd.System << endl
               << "Enumerations: " << print_optional(ssd.Enumerations).str()
               << "Units: " << print_optional(ssd.Units).str()
               << "DefaultExperiment: " << print_optional(ssd.DefaultExperiment).str()
               << "Annotations: " << print_optional(ssd.Annotations).str()
               << " }\n";
            return os;
        }
    };
}