
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
    string SystemGeometry::to_string(void) const
    {
        return "SystemGeometry { \n"

               "}";
    }

     // ConnectorGeometry
    string ConnectorGeometry::to_string(void) const
    {
        return "ConnectorGeometry { \n"

               "}";
    }

     // ElementGeometry
    string ElementGeometry::to_string(void) const
    {
        return "ElementGeometry { \n"

               "}";
    }

     // ConnectionGeometry
    string ConnectionGeometry::to_string(void) const
    {
        return "ConnectionGeometry { \n"

               "}";
    }

     // TSignalDictionaries
    string TSignalDictionaries::to_string(void) const
    {
        return "TSignalDictionaries { \n"

               "}";
    }

     // TParameterBindings
    string TParameterBindings::to_string(void) const
    {
        return "TParameterBindings { \n"

               "}";
    }

     // GraphicalElements
    string GraphicalElements::to_string(void) const
    {
        return "GraphicalElements { \n"

               "}";
    }

     // TDefaultExperiment
    string TDefaultExperiment::to_string(void) const
    {
        return "TDefaultExperiment { \n"

               "}";
    }

     // Connection
    string Connection::to_string(void) const
    {
        return "Connection { \n"
               "startElement                      : " + to_str( startElement                      ) + "\n" +
               "startConnector                    : " + to_str( startConnector                    ) + "\n" +
               "endElement                        : " + to_str( endElement                        ) + "\n" +
               "endConnector                      : " + to_str( endConnector                      ) + "\n" +
               "suppressUnitConversion            : " + to_str( suppressUnitConversion            ) + "\n" +
               "LinearTransformation              : " + to_str( LinearTransformation              ) + "\n" +
               "BooleanMappingTransformation      : " + to_str( BooleanMappingTransformation      ) + "\n" +
               "IntegerMappingTransformation      : " + to_str( IntegerMappingTransformation      ) + "\n" +
               "EnumerationMappingTransformation  : " + to_str( EnumerationMappingTransformation  ) + "\n" +
               "ConnectionGeometry                : " + to_str( ConnectionGeometry                ) + "\n" +
               "Annotations                       : " + to_str( Annotations                       ) + "\n" +
               "}";
    }

     // Connections
    string Connections::to_string(void) const
    {
        return "Connections { \n"
               "Connection  : " + to_str( Connection  ) + "\n" +
               "}";
    }

     // Connector
    string Connector::to_string(void) const
    {
        return "Connector { \n"
               "id                 : " + to_str( id                 ) + "\n" +
               "description        : " + to_str( description        ) + "\n" +
               "name               : " + to_str( name               ) + "\n" +
               "kind               : " + to_str( kind               ) + "\n" +
               "Real               : " + to_str( Real               ) + "\n" +
               "Integer            : " + to_str( Integer            ) + "\n" +
               "Boolean            : " + to_str( Boolean            ) + "\n" +
               "String             : " + to_str( String             ) + "\n" +
               "Enumeration        : " + to_str( Enumeration        ) + "\n" +
               "Binary             : " + to_str( Binary             ) + "\n" +
               "ConnectorGeometry  : " + to_str( ConnectorGeometry  ) + "\n" +
               "Annotations        : " + to_str( Annotations        ) + "\n" +
               "}";
    }

     // TConnectors
    string TConnectors::to_string(void) const
    {
        return "TConnectors { \n"
               "Connector  : " + to_str( Connector  ) + "\n" +
               "}";
    }

     // TComponent
    string TComponent::to_string(void) const
    {
        return "TComponent { \n"
               "id                 : " + to_str( id                 ) + "\n" +
               "description        : " + to_str( description        ) + "\n" +
               "name               : " + to_str( name               ) + "\n" +
               "Connectors         : " + to_str( Connectors         ) + "\n" +
               "ElementGeometry    : " + to_str( ElementGeometry    ) + "\n" +
               "ParameterBindings  : " + to_str( ParameterBindings  ) + "\n" +
               "type               : " + to_str( type               ) + "\n" +
               "source             : " + to_str( source             ) + "\n" +
               "implementation     : " + to_str( implementation     ) + "\n" +
               "Annotations        : " + to_str( Annotations        ) + "\n" +
               "}";
    }

     // TSignalDictionaryReference
    string TSignalDictionaryReference::to_string(void) const
    {
        return "TSignalDictionaryReference { \n"
               "dictionary         : " + to_str( dictionary         ) + "\n" +
               "Connectors         : " + to_str( Connectors         ) + "\n" +
               "ElementGeometry    : " + to_str( ElementGeometry    ) + "\n" +
               "ParameterBindings  : " + to_str( ParameterBindings  ) + "\n" +
               "Annotations        : " + to_str( Annotations        ) + "\n" +
               "}";
    }

     // Elements
    string Elements::to_string(void) const
    {
        return "Elements { \n"
               "Component                  : " + to_str( Component                  ) + "\n" +
               "SignalDictionaryReference  : " + to_str( SignalDictionaryReference  ) + "\n" +
               "System                     : " + to_str( System                     ) + "\n" +
               "}";
    }

     // TSystem
    string TSystem::to_string(void) const
    {
        return "TSystem { \n"
               "id                  : " + to_str( id                  ) + "\n" +
               "description         : " + to_str( description         ) + "\n" +
               "name                : " + to_str( name                ) + "\n" +
               "Connectors          : " + to_str( Connectors          ) + "\n" +
               "ElementGeometry     : " + to_str( ElementGeometry     ) + "\n" +
               "ParameterBindings   : " + to_str( ParameterBindings   ) + "\n" +
               "Elements            : " + to_str( Elements            ) + "\n" +
               "Connections         : " + to_str( Connections         ) + "\n" +
               "SignalDictionaries  : " + to_str( SignalDictionaries  ) + "\n" +
               "SystemGeometry      : " + to_str( SystemGeometry      ) + "\n" +
               "GraphicalElements   : " + to_str( GraphicalElements   ) + "\n" +
               "Annotations         : " + to_str( Annotations         ) + "\n" +
               "}";
    }

     // SystemStructureDescription
    string SystemStructureDescription::to_string(void) const
    {
        return "SystemStructureDescription { \n"
               "version                : " + to_str( version                ) + "\n" +
               "name                   : " + to_str( name                   ) + "\n" +
               "id                     : " + to_str( id                     ) + "\n" +
               "description            : " + to_str( description            ) + "\n" +
               "author                 : " + to_str( author                 ) + "\n" +
               "fileversion            : " + to_str( fileversion            ) + "\n" +
               "copyright              : " + to_str( copyright              ) + "\n" +
               "license                : " + to_str( license                ) + "\n" +
               "generationTool         : " + to_str( generationTool         ) + "\n" +
               "generationDateAndTime  : " + to_str( generationDateAndTime  ) + "\n" +
               "System                 : " + to_str( System                 ) + "\n" +
               "Enumerations           : " + to_str( Enumerations           ) + "\n" +
               "Units                  : " + to_str( Units                  ) + "\n" +
               "DefaultExperiment      : " + to_str( DefaultExperiment      ) + "\n" +
               "Annotations            : " + to_str( Annotations            ) + "\n" +
               "}";
    }


}
