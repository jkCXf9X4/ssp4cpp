

// This is a generated file, do not alter
// it is based on ssp1_ssd.toml

#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureDescription.hpp"
#include "ssp4cpp/utils/string.hpp"

#include <string>

namespace ssp4cpp::ssp1::ssd
{


     // SystemGeometry
    std::string SystemGeometry::to_string(void) const
    {
        return "SystemGeometry { \n"

               "}";
    }

     // ConnectorGeometry
    std::string ConnectorGeometry::to_string(void) const
    {
        return "ConnectorGeometry { \n"

               "}";
    }

     // ElementGeometry
    std::string ElementGeometry::to_string(void) const
    {
        return "ElementGeometry { \n"

               "}";
    }

     // ConnectionGeometry
    std::string ConnectionGeometry::to_string(void) const
    {
        return "ConnectionGeometry { \n"

               "}";
    }

     // SignalDictionary
    std::string SignalDictionary::to_string(void) const
    {
        return "SignalDictionary { \n"

               "}";
    }

     // TSignalDictionaries
    std::string TSignalDictionaries::to_string(void) const
    {
        return "TSignalDictionaries { \n"
               "SignalDictionaries  : " + utils::str::to_string( SignalDictionaries  ) + "\n" +
               "}";
    }

     // ParameterMapping
    std::string ParameterMapping::to_string(void) const
    {
        return "ParameterMapping { \n"
               "id                : " + utils::str::to_string( id                ) + "\n" +
               "description       : " + utils::str::to_string( description       ) + "\n" +
               "type              : " + utils::str::to_string( type              ) + "\n" +
               "source            : " + utils::str::to_string( source            ) + "\n" +
               "sourceBase        : " + utils::str::to_string( sourceBase        ) + "\n" +
               "ParameterMapping  : " + utils::str::to_string( ParameterMapping  ) + "\n" +
               "}";
    }

     // ParameterBinding
    std::string ParameterBinding::to_string(void) const
    {
        return "ParameterBinding { \n"
               "id                : " + utils::str::to_string( id                ) + "\n" +
               "description       : " + utils::str::to_string( description       ) + "\n" +
               "type              : " + utils::str::to_string( type              ) + "\n" +
               "source            : " + utils::str::to_string( source            ) + "\n" +
               "sourceBase        : " + utils::str::to_string( sourceBase        ) + "\n" +
               "prefix            : " + utils::str::to_string( prefix            ) + "\n" +
               "ParameterValues   : " + utils::str::to_string( ParameterValues   ) + "\n" +
               "ParameterMapping  : " + utils::str::to_string( ParameterMapping  ) + "\n" +
               "}";
    }

     // TParameterBindings
    std::string TParameterBindings::to_string(void) const
    {
        return "TParameterBindings { \n"
               "ParameterBindings  : " + utils::str::to_string( ParameterBindings  ) + "\n" +
               "}";
    }

     // GraphicalElements
    std::string GraphicalElements::to_string(void) const
    {
        return "GraphicalElements { \n"

               "}";
    }

     // TDefaultExperiment
    std::string TDefaultExperiment::to_string(void) const
    {
        return "TDefaultExperiment { \n"
               "startTime    : " + utils::str::to_string( startTime    ) + "\n" +
               "stopTime     : " + utils::str::to_string( stopTime     ) + "\n" +
               "Annotations  : " + utils::str::to_string( Annotations  ) + "\n" +
               "}";
    }

     // Connection
    std::string Connection::to_string(void) const
    {
        return "Connection { \n"
               "id                                : " + utils::str::to_string( id                                ) + "\n" +
               "description                       : " + utils::str::to_string( description                       ) + "\n" +
               "startElement                      : " + utils::str::to_string( startElement                      ) + "\n" +
               "startConnector                    : " + utils::str::to_string( startConnector                    ) + "\n" +
               "endElement                        : " + utils::str::to_string( endElement                        ) + "\n" +
               "endConnector                      : " + utils::str::to_string( endConnector                      ) + "\n" +
               "suppressUnitConversion            : " + utils::str::to_string( suppressUnitConversion            ) + "\n" +
               "LinearTransformation              : " + utils::str::to_string( LinearTransformation              ) + "\n" +
               "BooleanMappingTransformation      : " + utils::str::to_string( BooleanMappingTransformation      ) + "\n" +
               "IntegerMappingTransformation      : " + utils::str::to_string( IntegerMappingTransformation      ) + "\n" +
               "EnumerationMappingTransformation  : " + utils::str::to_string( EnumerationMappingTransformation  ) + "\n" +
               "ConnectionGeometry                : " + utils::str::to_string( ConnectionGeometry                ) + "\n" +
               "Annotations                       : " + utils::str::to_string( Annotations                       ) + "\n" +
               "information_delay                 : " + utils::str::to_string( information_delay                 ) + "\n" +
               "}";
    }

     // Connections
    std::string Connections::to_string(void) const
    {
        return "Connections { \n"
               "Connections  : " + utils::str::to_string( Connections  ) + "\n" +
               "}";
    }

     // Connector
    std::string Connector::to_string(void) const
    {
        return "Connector { \n"
               "id                 : " + utils::str::to_string( id                 ) + "\n" +
               "description        : " + utils::str::to_string( description        ) + "\n" +
               "name               : " + utils::str::to_string( name               ) + "\n" +
               "kind               : " + utils::str::to_string( kind               ) + "\n" +
               "Real               : " + utils::str::to_string( Real               ) + "\n" +
               "Integer            : " + utils::str::to_string( Integer            ) + "\n" +
               "Boolean            : " + utils::str::to_string( Boolean            ) + "\n" +
               "String             : " + utils::str::to_string( String             ) + "\n" +
               "Enumeration        : " + utils::str::to_string( Enumeration        ) + "\n" +
               "Binary             : " + utils::str::to_string( Binary             ) + "\n" +
               "ConnectorGeometry  : " + utils::str::to_string( ConnectorGeometry  ) + "\n" +
               "Annotations        : " + utils::str::to_string( Annotations        ) + "\n" +
               "}";
    }

     // TConnectors
    std::string TConnectors::to_string(void) const
    {
        return "TConnectors { \n"
               "Connectors  : " + utils::str::to_string( Connectors  ) + "\n" +
               "}";
    }

     // TComponent
    std::string TComponent::to_string(void) const
    {
        return "TComponent { \n"
               "id                 : " + utils::str::to_string( id                 ) + "\n" +
               "description        : " + utils::str::to_string( description        ) + "\n" +
               "name               : " + utils::str::to_string( name               ) + "\n" +
               "Connectors         : " + utils::str::to_string( Connectors         ) + "\n" +
               "ElementGeometry    : " + utils::str::to_string( ElementGeometry    ) + "\n" +
               "ParameterBindings  : " + utils::str::to_string( ParameterBindings  ) + "\n" +
               "type               : " + utils::str::to_string( type               ) + "\n" +
               "source             : " + utils::str::to_string( source             ) + "\n" +
               "implementation     : " + utils::str::to_string( implementation     ) + "\n" +
               "Annotations        : " + utils::str::to_string( Annotations        ) + "\n" +
               "}";
    }

     // TSignalDictionaryReference
    std::string TSignalDictionaryReference::to_string(void) const
    {
        return "TSignalDictionaryReference { \n"
               "id                 : " + utils::str::to_string( id                 ) + "\n" +
               "description        : " + utils::str::to_string( description        ) + "\n" +
               "name               : " + utils::str::to_string( name               ) + "\n" +
               "Connectors         : " + utils::str::to_string( Connectors         ) + "\n" +
               "ElementGeometry    : " + utils::str::to_string( ElementGeometry    ) + "\n" +
               "ParameterBindings  : " + utils::str::to_string( ParameterBindings  ) + "\n" +
               "dictionary         : " + utils::str::to_string( dictionary         ) + "\n" +
               "Annotations        : " + utils::str::to_string( Annotations        ) + "\n" +
               "}";
    }

     // Elements
    std::string Elements::to_string(void) const
    {
        return "Elements { \n"
               "Components                  : " + utils::str::to_string( Components                  ) + "\n" +
               "SignalDictionaryReferences  : " + utils::str::to_string( SignalDictionaryReferences  ) + "\n" +
               "Systems                     : " + utils::str::to_string( Systems                     ) + "\n" +
               "}";
    }

     // TSystem
    std::string TSystem::to_string(void) const
    {
        return "TSystem { \n"
               "id                  : " + utils::str::to_string( id                  ) + "\n" +
               "description         : " + utils::str::to_string( description         ) + "\n" +
               "name                : " + utils::str::to_string( name                ) + "\n" +
               "Connectors          : " + utils::str::to_string( Connectors          ) + "\n" +
               "ElementGeometry     : " + utils::str::to_string( ElementGeometry     ) + "\n" +
               "ParameterBindings   : " + utils::str::to_string( ParameterBindings   ) + "\n" +
               "Elements            : " + utils::str::to_string( Elements            ) + "\n" +
               "Connections         : " + utils::str::to_string( Connections         ) + "\n" +
               "SignalDictionaries  : " + utils::str::to_string( SignalDictionaries  ) + "\n" +
               "SystemGeometry      : " + utils::str::to_string( SystemGeometry      ) + "\n" +
               "GraphicalElements   : " + utils::str::to_string( GraphicalElements   ) + "\n" +
               "Annotations         : " + utils::str::to_string( Annotations         ) + "\n" +
               "}";
    }

     // SystemStructureDescription
    std::string SystemStructureDescription::to_string(void) const
    {
        return "SystemStructureDescription { \n"
               "version                : " + utils::str::to_string( version                ) + "\n" +
               "name                   : " + utils::str::to_string( name                   ) + "\n" +
               "id                     : " + utils::str::to_string( id                     ) + "\n" +
               "description            : " + utils::str::to_string( description            ) + "\n" +
               "author                 : " + utils::str::to_string( author                 ) + "\n" +
               "fileversion            : " + utils::str::to_string( fileversion            ) + "\n" +
               "copyright              : " + utils::str::to_string( copyright              ) + "\n" +
               "license                : " + utils::str::to_string( license                ) + "\n" +
               "generationTool         : " + utils::str::to_string( generationTool         ) + "\n" +
               "generationDateAndTime  : " + utils::str::to_string( generationDateAndTime  ) + "\n" +
               "System                 : " + utils::str::to_string( System                 ) + "\n" +
               "Enumerations           : " + utils::str::to_string( Enumerations           ) + "\n" +
               "Units                  : " + utils::str::to_string( Units                  ) + "\n" +
               "DefaultExperiment      : " + utils::str::to_string( DefaultExperiment      ) + "\n" +
               "Annotations            : " + utils::str::to_string( Annotations            ) + "\n" +
               "}";
    }

}
