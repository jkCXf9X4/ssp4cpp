
#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "SystemStructureDescription.hpp"
#include "to_string.hpp"

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

     // ConnectorGeometry
    string to_string(const ConnectorGeometry &obj)
    {
        return "ConnectorGeometry { \n"

               "}";
    }

     // ElementGeometry
    string to_string(const ElementGeometry &obj)
    {
        return "ElementGeometry { \n"

               "}";
    }

     // ConnectionGeometry
    string to_string(const ConnectionGeometry &obj)
    {
        return "ConnectionGeometry { \n"

               "}";
    }

     // TSignalDictionaries
    string to_string(const TSignalDictionaries &obj)
    {
        return "TSignalDictionaries { \n"

               "}";
    }

     // TParameterBindings
    string to_string(const TParameterBindings &obj)
    {
        return "TParameterBindings { \n"

               "}";
    }

     // GraphicalElements
    string to_string(const GraphicalElements &obj)
    {
        return "GraphicalElements { \n"

               "}";
    }

     // TDefaultExperiment
    string to_string(const TDefaultExperiment &obj)
    {
        return "TDefaultExperiment { \n"

               "}";
    }

     // Connection
    string to_string(const Connection &obj)
    {
        return "Connection { \n"
               "startElement                       : " + to_str( obj.startElement )                                               + "\n" +
               "startConnector                     : " + to_str( obj.startConnector )                                             + "\n" +
               "endElement                         : " + to_str( obj.endElement )                                                 + "\n" +
               "endConnector                       : " + to_str( obj.endConnector )                                               + "\n" +
               "suppressUnitConversion             : " + to_str( obj.suppressUnitConversion )                                     + "\n" +
               "LinearTransformation               : " + to_str( obj.LinearTransformation )                                       + "\n" +
               "BooleanMappingTransformation       : " + to_str( obj.BooleanMappingTransformation )                               + "\n" +
               "IntegerMappingTransformation       : " + to_str( obj.IntegerMappingTransformation )                               + "\n" +
               "EnumerationMappingTransformation   : " + to_str( obj.EnumerationMappingTransformation )                           + "\n" +
               "ConnectionGeometry                 : " + to_str( obj.ConnectionGeometry )                                         + "\n" +
               "Annotations                        : " + to_str( obj.Annotations )                                                + "\n" +
               "}";
    }

     // Connections
    string to_string(const Connections &obj)
    {
        return "Connections { \n"
               "list   : " + to_str(obj.list    ) + "\n" +
               "}";
    }

     // Connector
    string to_string(const Connector &obj)
    {
        return "Connector { \n"
               "id                  : " + to_str( obj.id )                                          + "\n" +
               "description         : " + to_str( obj.description )                                 + "\n" +
               "name                : " + to_str( obj.name )                                        + "\n" +
               "kind                : " + to_str( obj.kind )                                        + "\n" +
               "Real                : " + to_str( obj.Real )                                        + "\n" +
               "Integer             : " + to_str( obj.Integer )                                     + "\n" +
               "Boolean             : " + to_str( obj.Boolean )                                     + "\n" +
               "String              : " + to_str( obj.String )                                      + "\n" +
               "Enumeration         : " + to_str( obj.Enumeration )                                 + "\n" +
               "Binary              : " + to_str( obj.Binary )                                      + "\n" +
               "ConnectorGeometry   : " + to_str( obj.ConnectorGeometry )                           + "\n" +
               "Annotations         : " + to_str( obj.Annotations )                                 + "\n" +
               "}";
    }

     // TConnectors
    string to_string(const TConnectors &obj)
    {
        return "TConnectors { \n"
               "list   : " + to_str(obj.list    ) + "\n" +
               "}";
    }

     // TComponent
    string to_string(const TComponent &obj)
    {
        return "TComponent { \n"
               "id                   : " + to_str( obj.id )                                           + "\n" +
               "description          : " + to_str( obj.description )                                  + "\n" +
               "name                 : " + to_str( obj.name )                                         + "\n" +
               "Connectors           : " + to_str( obj.Connectors )                                   + "\n" +
               "ElementGeometry      : " + to_str( obj.ElementGeometry )                              + "\n" +
               "TParameterBindings   : " + to_str( obj.TParameterBindings )                           + "\n" +
               "component_type_str   : " + to_str( obj.component_type_str )                           + "\n" +
               "component_type       : " + to_str( obj.component_type )                               + "\n" +
               "source               : " + to_str( obj.source )                                       + "\n" +
               "implementation       : " + to_str( obj.implementation )                               + "\n" +
               "Annotations          : " + to_str( obj.Annotations )                                  + "\n" +
               "}";
    }

     // TSignalDictionaryReference
    string to_string(const TSignalDictionaryReference &obj)
    {
        return "TSignalDictionaryReference { \n"
               "dictionary           : " + to_str( obj.dictionary )                                   + "\n" +
               "Connectors           : " + to_str( obj.Connectors )                                   + "\n" +
               "ElementGeometry      : " + to_str( obj.ElementGeometry )                              + "\n" +
               "TParameterBindings   : " + to_str( obj.TParameterBindings )                           + "\n" +
               "Annotations          : " + to_str( obj.Annotations )                                  + "\n" +
               "}";
    }

     // Elements
    string to_string(const Elements &obj)
    {
        return "Elements { \n"
               "components                     : " + to_str(obj.components                      ) + "\n" +
               "signal_dictionary_references   : " + to_str(obj.signal_dictionary_references    ) + "\n" +
               "systems                        : " + to_str(obj.systems                         ) + "\n" +
               "}";
    }

     // TSystem
    string to_string(const TSystem &obj)
    {
        return "TSystem { \n"
               "id                   : " + to_str( obj.id )                                           + "\n" +
               "description          : " + to_str( obj.description )                                  + "\n" +
               "name                 : " + to_str( obj.name )                                         + "\n" +
               "Connectors           : " + to_str( obj.Connectors )                                   + "\n" +
               "ElementGeometry      : " + to_str( obj.ElementGeometry )                              + "\n" +
               "ParameterBindings    : " + to_str( obj.ParameterBindings )                            + "\n" +
               "Elements             : " + to_str( obj.Elements )                                     + "\n" +
               "Connections          : " + to_str( obj.Connections )                                  + "\n" +
               "SignalDictionaries   : " + to_str( obj.SignalDictionaries )                           + "\n" +
               "SystemGeometry       : " + to_str( obj.SystemGeometry )                               + "\n" +
               "GraphicalElements    : " + to_str( obj.GraphicalElements )                            + "\n" +
               "Annotations          : " + to_str( obj.Annotations )                                  + "\n" +
               "}";
    }

     // SystemStructureDescription
    string to_string(const SystemStructureDescription &obj)
    {
        return "SystemStructureDescription { \n"
               "version                 : " + to_str( obj.version )                                         + "\n" +
               "name                    : " + to_str( obj.name )                                            + "\n" +
               "id                      : " + to_str( obj.id )                                              + "\n" +
               "description             : " + to_str( obj.description )                                     + "\n" +
               "author                  : " + to_str( obj.author )                                          + "\n" +
               "fileversion             : " + to_str( obj.fileversion )                                     + "\n" +
               "copyright               : " + to_str( obj.copyright )                                       + "\n" +
               "license                 : " + to_str( obj.license )                                         + "\n" +
               "generationTool          : " + to_str( obj.generationTool )                                  + "\n" +
               "generationDateAndTime   : " + to_str( obj.generationDateAndTime )                           + "\n" +
               "System                  : " + to_string( obj.System )                                       + "\n" +
               "Enumerations            : " + to_str( obj.Enumerations )                                    + "\n" +
               "Units                   : " + to_str( obj.Units )                                           + "\n" +
               "DefaultExperiment       : " + to_str( obj.DefaultExperiment )                               + "\n" +
               "Annotations             : " + to_str( obj.Annotations )                                     + "\n" +
               "}";
    }


}
