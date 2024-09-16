
#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "SystemStructureDescription.hpp"
#include "print_misc.hpp"

namespace ssp4cpp::ssp1::ssd
{
    using namespace std;
    using namespace ssp4cpp::ssp1;

    string to_string(const SystemGeometry &obj)
    {
        return "SystemGeometry()";
    }

    string to_string(const ConnectorGeometry &obj)
    {
        return "ConnectorGeometry()";
    }

    string to_string(const ElementGeometry &obj)
    {
        return "ElementGeometry()";
    }

    string to_string(const ConnectionGeometry &obj)
    {
        return "ConnectionGeometry()";
    }

    string to_string(const TSignalDictionaries &obj)
    {
        return "TSignalDictionaries()";
    }

    string to_string(const TParameterBindings &obj)
    {
        return "TParameterBindings()";
    }

    string to_string(const GraphicalElements &obj)
    {
        return "GraphicalElements()";
    }

    string to_string(const TDefaultExperiment &obj)
    {
        return "TDefaultExperiment()";
    }

    string to_string(const Connection &conn)
    {
        return "Connection {\n" 
               "startElement: " + conn.startElement.value_or("null") + "\n" +
               "startConnector: " + conn.startConnector + "\n" +
               "endElement: " + conn.endElement.value_or("null") + "\n" +
               "endConnector: " + conn.endConnector + "\n" +
               "suppressUnitConversion: " + std::to_string(conn.suppressUnitConversion.value_or(false)) +
               "LinearTransformation: " + to_string_optional(conn.LinearTransformation) +
               "BooleanMappingTransformation: " + to_string_optional(conn.BooleanMappingTransformation) +
               "IntegerMappingTransformation: " + to_string_optional(conn.IntegerMappingTransformation) +
               "EnumerationMappingTransformation: " + to_string_optional(conn.EnumerationMappingTransformation) +
               "ConnectionGeometry: " + to_string_optional(conn.ConnectionGeometry) +
               "Annotations: " + to_string_optional(conn.Annotations) +
               " }";
    }

    string to_string(const Connections &conns)
    {
        string result = "Connections { \n";
        for (const auto &conn : conns.list)
        {
            result += to_string(conn) + "\n";
        }
        result += " }";
        return result;
    }

    string to_string(const Connector &conn)
    {
        return "Connector {\n" 
               "id: " + conn.id.value_or("null") + "\n" +
               "description: " + conn.description.value_or("null") + "\n" +
               "name: " + conn.name + "\n" +
               "kind: " + conn.kind + "\n" +
               "Real: " + to_string_optional(conn.Real) +
               "Integer: " + to_string_optional(conn.Integer) +
               "Boolean: " + to_string_optional(conn.Boolean) +
               "String: " + to_string_optional(conn.String) +
               "Enumeration: " + to_string_optional(conn.Enumeration) +
               "Binary: " + to_string_optional(conn.Binary) +
               "ConnectorGeometry: " + to_string_optional(conn.ConnectorGeometry) +
               "Annotations: " + to_string_optional(conn.Annotations) +
               " }";
    }

    string to_string(const TConnectors &conns)
    {
        string result = "TConnectors {\n";
        for (const auto &conn : conns.list)
        {
            result += to_string(conn) + "\n";
        }
        result += " }";
        return result;
    }

    string to_string(const TComponent &comp)
    {
        return "TComponent {\n" 
               "id: " + comp.id.value_or("null") + "\n" +
               "description: " + comp.description.value_or("null") + "\n" +
               "name: " + comp.name.value_or("null") + "\n" +
               "Connectors: " + to_string_optional(comp.Connectors) +
               "ElementGeometry: " + to_string_optional(comp.ElementGeometry) +
               "TParameterBindings: " + to_string_optional(comp.TParameterBindings) +
               "component_type: " + comp.component_type.value_or("null") + "\n" +
               "source: " + comp.source + "\n" +
               "implementation: " + comp.implementation.value_or("null") + "\n" +
               "Annotations: " + to_string_optional(comp.Annotations) +
               " }";
    }

    string to_string(const TSignalDictionaryReference &ref)
    {
        return "TSignalDictionaryReference {\n"
               "dictionary: " + ref.dictionary + "\n" +
               "Connectors: " + to_string_optional(ref.Connectors) +
               "ElementGeometry: " + to_string_optional(ref.ElementGeometry) +
               "TParameterBindings: " + to_string_optional(ref.TParameterBindings) +
               "Annotations: " + to_string_optional(ref.Annotations) +
               " }";
    }

    string to_string(const Elements &elems)
    {
        string result = "Elements {\ncomponents {\n";
        for (const auto &comp : elems.components)
        {
            result += to_string(comp) + "\n";
        }
        result += "} \nsignal_dictionary_references {\n";
        for (const auto &ref : elems.signal_dictionary_references)
        {
            result += to_string(ref) + "\n";
        }
        result += "} \nsystems {\n";
        for (const auto &sys : elems.systems)
        {
            result += to_string(sys) + "\n";
        }
        result += "}\n}\n";
        return result;
    }

    string to_string(const TSystem &sys)
    {
        return "TSystem {\n"
               "id: " + sys.id.value_or("null") + "\n" +
               "description: " + sys.description.value_or("null") + "\n" +
               "name: " + sys.name.value_or("null") + "\n" +
               "Connectors: " + to_string_optional(sys.Connectors) +
               "ElementGeometry: " + to_string_optional(sys.ElementGeometry) +
               "ParameterBindings: " + to_string_optional(sys.ParameterBindings) +
               "Elements: " + to_string_optional(sys.Elements) +
               "Connections: " + to_string_optional(sys.Connections) +
               "SignalDictionaries: " + to_string_optional(sys.SignalDictionaries) +
               "SystemGeometry: " + to_string_optional(sys.SystemGeometry) +
               "GraphicalElements: " + to_string_optional(sys.GraphicalElements) +
               "Annotations: " + to_string_optional(sys.Annotations) +
               " }\n";
    }

    string to_string(const SystemStructureDescription &ssd)
    {
        return "SystemStructureDescription {\n"
               "version: " + ssd.version + "\n" +
               "name: " + ssd.name + "\n" +
               "id: " + ssd.id.value_or("null") + "\n" +
               "description: " + ssd.description.value_or("null") + "\n" +
               "author: " + ssd.author.value_or("null") + "\n" +
               "fileversion: " + ssd.fileversion.value_or("null") + "\n" +
               "copyright: " + ssd.copyright.value_or("null") + "\n" +
               "license: " + ssd.license.value_or("null") + "\n" +
               "generationTool: " + ssd.generationTool.value_or("null") + "\n" +
               "generationDateAndTime: " + ssd.generationDateAndTime.value_or("null") + "\n" +
               "System: \n" + to_string(ssd.System) + "\n" +
               "Enumerations: " + to_string_optional(ssd.Enumerations) +
               "Units: " + to_string_optional(ssd.Units) +
               "DefaultExperiment: " + to_string_optional(ssd.DefaultExperiment) +
               "Annotations: " + to_string_optional(ssd.Annotations) +
               " }\n";
    }
}