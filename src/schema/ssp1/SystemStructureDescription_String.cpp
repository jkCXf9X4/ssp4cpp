
#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "SystemStructureDescription.hpp"
#include "to_string.tpp"

using namespace std;
using namespace ssp4cpp::ssp1;

namespace ssp4cpp::ssp1::ssd
{
    // SystemGeometry
    string to_string(const SystemGeometry &obj)
    {
        return "SystemGeometry { \n"

               "}";
    }
    string to_string(const optional<SystemGeometry> &obj) { return to_string_optional(obj); }
    string to_string(const vector<SystemGeometry> &obj) { return to_string_vector(obj); }

     // ConnectorGeometry
    string to_string(const ConnectorGeometry &obj)
    {
        return "ConnectorGeometry { \n"

               "}";
    }
    string to_string(const optional<ConnectorGeometry> &obj) { return to_string_optional(obj); }
    string to_string(const vector<ConnectorGeometry> &obj) { return to_string_vector(obj); }

     // ElementGeometry
    string to_string(const ElementGeometry &obj)
    {
        return "ElementGeometry { \n"

               "}";
    }
    string to_string(const optional<ElementGeometry> &obj) { return to_string_optional(obj); }
    string to_string(const vector<ElementGeometry> &obj) { return to_string_vector(obj); }

     // ConnectionGeometry
    string to_string(const ConnectionGeometry &obj)
    {
        return "ConnectionGeometry { \n"

               "}";
    }
    string to_string(const optional<ConnectionGeometry> &obj) { return to_string_optional(obj); }
    string to_string(const vector<ConnectionGeometry> &obj) { return to_string_vector(obj); }

     // TSignalDictionaries
    string to_string(const TSignalDictionaries &obj)
    {
        return "TSignalDictionaries { \n"

               "}";
    }
    string to_string(const optional<TSignalDictionaries> &obj) { return to_string_optional(obj); }
    string to_string(const vector<TSignalDictionaries> &obj) { return to_string_vector(obj); }

     // TParameterBindings
    string to_string(const TParameterBindings &obj)
    {
        return "TParameterBindings { \n"

               "}";
    }
    string to_string(const optional<TParameterBindings> &obj) { return to_string_optional(obj); }
    string to_string(const vector<TParameterBindings> &obj) { return to_string_vector(obj); }

     // GraphicalElements
    string to_string(const GraphicalElements &obj)
    {
        return "GraphicalElements { \n"

               "}";
    }
    string to_string(const optional<GraphicalElements> &obj) { return to_string_optional(obj); }
    string to_string(const vector<GraphicalElements> &obj) { return to_string_vector(obj); }

     // TDefaultExperiment
    string to_string(const TDefaultExperiment &obj)
    {
        return "TDefaultExperiment { \n"

               "}";
    }
    string to_string(const optional<TDefaultExperiment> &obj) { return to_string_optional(obj); }
    string to_string(const vector<TDefaultExperiment> &obj) { return to_string_vector(obj); }

     // Connection
    string to_string(const Connection &obj)
    {
        return "Connection { \n"
               "startElement                       : " + obj.startElement.value_or("null")                                        + "\n" +
               "startConnector                     : " + obj.startConnector                                                       + "\n" +
               "endElement                         : " + obj.endElement.value_or("null")                                          + "\n" +
               "endConnector                       : " + obj.endConnector                                                         + "\n" +
               "suppressUnitConversion             : " + std::to_string( obj.suppressUnitConversion.value_or(false) )             + "\n" +
               "LinearTransformation               : " + to_string( obj.LinearTransformation )                                    + "\n" +
               "BooleanMappingTransformation       : " + to_string( obj.BooleanMappingTransformation )                            + "\n" +
               "IntegerMappingTransformation       : " + to_string( obj.IntegerMappingTransformation )                            + "\n" +
               "EnumerationMappingTransformation   : " + to_string( obj.EnumerationMappingTransformation )                        + "\n" +
               "ConnectionGeometry                 : " + to_string( obj.ConnectionGeometry )                                      + "\n" +
               "Annotations                        : " + to_string( obj.Annotations )                                             + "\n" +
               "}";
    }
    string to_string(const optional<Connection> &obj) { return to_string_optional(obj); }
    string to_string(const vector<Connection> &obj) { return to_string_vector(obj); }

     // Connections
    string to_string(const Connections &obj)
    {
        return "Connections { \n"
               "list   : " + to_string(obj.list    ) + "\n" +
               "}";
    }
    string to_string(const optional<Connections> &obj) { return to_string_optional(obj); }
    string to_string(const vector<Connections> &obj) { return to_string_vector(obj); }

     // Connector
    string to_string(const Connector &obj)
    {
        return "Connector { \n"
               "id                  : " + obj.id.value_or("null")                                   + "\n" +
               "description         : " + obj.description.value_or("null")                          + "\n" +
               "name                : " + obj.name                                                  + "\n" +
               "kind                : " + obj.kind                                                  + "\n" +
               "Real                : " + to_string( obj.Real )                                     + "\n" +
               "Integer             : " + to_string( obj.Integer )                                  + "\n" +
               "Boolean             : " + to_string( obj.Boolean )                                  + "\n" +
               "String              : " + to_string( obj.String )                                   + "\n" +
               "Enumeration         : " + to_string( obj.Enumeration )                              + "\n" +
               "Binary              : " + to_string( obj.Binary )                                   + "\n" +
               "ConnectorGeometry   : " + to_string( obj.ConnectorGeometry )                        + "\n" +
               "Annotations         : " + to_string( obj.Annotations )                              + "\n" +
               "}";
    }
    string to_string(const optional<Connector> &obj) { return to_string_optional(obj); }
    string to_string(const vector<Connector> &obj) { return to_string_vector(obj); }

     // TConnectors
    string to_string(const TConnectors &obj)
    {
        return "TConnectors { \n"
               "list   : " + to_string(obj.list    ) + "\n" +
               "}";
    }
    string to_string(const optional<TConnectors> &obj) { return to_string_optional(obj); }
    string to_string(const vector<TConnectors> &obj) { return to_string_vector(obj); }

     // TComponent
    string to_string(const TComponent &obj)
    {
        return "TComponent { \n"
               "id                   : " + obj.id.value_or("null")                                    + "\n" +
               "description          : " + obj.description.value_or("null")                           + "\n" +
               "name                 : " + obj.name.value_or("null")                                  + "\n" +
               "Connectors           : " + to_string( obj.Connectors )                                + "\n" +
               "ElementGeometry      : " + to_string( obj.ElementGeometry )                           + "\n" +
               "TParameterBindings   : " + to_string( obj.TParameterBindings )                        + "\n" +
               "component_type_str   : " + obj.component_type_str.value_or("null")                    + "\n" +
               "component_type       : " + to_string( obj.component_type )                            + "\n" +
               "source               : " + obj.source                                                 + "\n" +
               "implementation       : " + obj.implementation.value_or("null")                        + "\n" +
               "Annotations          : " + to_string( obj.Annotations )                               + "\n" +
               "}";
    }
    string to_string(const optional<TComponent> &obj) { return to_string_optional(obj); }
    string to_string(const vector<TComponent> &obj) { return to_string_vector(obj); }

     // TSignalDictionaryReference
    string to_string(const TSignalDictionaryReference &obj)
    {
        return "TSignalDictionaryReference { \n"
               "dictionary           : " + obj.dictionary                                             + "\n" +
               "Connectors           : " + to_string( obj.Connectors )                                + "\n" +
               "ElementGeometry      : " + to_string( obj.ElementGeometry )                           + "\n" +
               "TParameterBindings   : " + to_string( obj.TParameterBindings )                        + "\n" +
               "Annotations          : " + to_string( obj.Annotations )                               + "\n" +
               "}";
    }
    string to_string(const optional<TSignalDictionaryReference> &obj) { return to_string_optional(obj); }
    string to_string(const vector<TSignalDictionaryReference> &obj) { return to_string_vector(obj); }

     // Elements
    string to_string(const Elements &obj)
    {
        return "Elements { \n"
               "components                     : " + to_string(obj.components                      ) + "\n" +
               "signal_dictionary_references   : " + to_string(obj.signal_dictionary_references    ) + "\n" +
               "systems                        : " + to_string(obj.systems                         ) + "\n" +
               "}";
    }
    string to_string(const optional<Elements> &obj) { return to_string_optional(obj); }
    string to_string(const vector<Elements> &obj) { return to_string_vector(obj); }

     // TSystem
    string to_string(const TSystem &obj)
    {
        return "TSystem { \n"
               "id                   : " + obj.id.value_or("null")                                    + "\n" +
               "description          : " + obj.description.value_or("null")                           + "\n" +
               "name                 : " + obj.name.value_or("null")                                  + "\n" +
               "Connectors           : " + to_string( obj.Connectors )                                + "\n" +
               "ElementGeometry      : " + to_string( obj.ElementGeometry )                           + "\n" +
               "ParameterBindings    : " + to_string( obj.ParameterBindings )                         + "\n" +
               "Elements             : " + to_string( obj.Elements )                                  + "\n" +
               "Connections          : " + to_string( obj.Connections )                               + "\n" +
               "SignalDictionaries   : " + to_string( obj.SignalDictionaries )                        + "\n" +
               "SystemGeometry       : " + to_string( obj.SystemGeometry )                            + "\n" +
               "GraphicalElements    : " + to_string( obj.GraphicalElements )                         + "\n" +
               "Annotations          : " + to_string( obj.Annotations )                               + "\n" +
               "}";
    }
    string to_string(const optional<TSystem> &obj) { return to_string_optional(obj); }
    string to_string(const vector<TSystem> &obj) { return to_string_vector(obj); }

     // SystemStructureDescription
    string to_string(const SystemStructureDescription &obj)
    {
        return "SystemStructureDescription { \n"
               "version                 : " + obj.version                                                   + "\n" +
               "name                    : " + obj.name                                                      + "\n" +
               "id                      : " + obj.id.value_or("null")                                       + "\n" +
               "description             : " + obj.description.value_or("null")                              + "\n" +
               "author                  : " + obj.author.value_or("null")                                   + "\n" +
               "fileversion             : " + obj.fileversion.value_or("null")                              + "\n" +
               "copyright               : " + obj.copyright.value_or("null")                                + "\n" +
               "license                 : " + obj.license.value_or("null")                                  + "\n" +
               "generationTool          : " + obj.generationTool.value_or("null")                           + "\n" +
               "generationDateAndTime   : " + obj.generationDateAndTime.value_or("null")                    + "\n" +
               "System                  : " + to_string( obj.System )                                        + "\n" +
               "Enumerations            : " + to_string( obj.Enumerations )                                 + "\n" +
               "Units                   : " + to_string( obj.Units )                                        + "\n" +
               "DefaultExperiment       : " + to_string( obj.DefaultExperiment )                            + "\n" +
               "Annotations             : " + to_string( obj.Annotations )                                  + "\n" +
               "}";
    }
    string to_string(const optional<SystemStructureDescription> &obj) { return to_string_optional(obj); }
    string to_string(const vector<SystemStructureDescription> &obj) { return to_string_vector(obj); }

}