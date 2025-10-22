

// This is a generated file, do not alter
// it is based on ssp1_ssd.toml

#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureDescription.hpp"
#include "ssp4cpp/utils/string.hpp"

#include <string>

namespace ssp4cpp::ssp1::ssd
{
    using namespace utils::str;


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
               "SignalDictionaries  : " + to_str( SignalDictionaries  ) + "\n" +
               "}";
    }

     // ParameterMapping
    std::string ParameterMapping::to_string(void) const
    {
        return "ParameterMapping { \n"
               "id                : " + to_str( id                ) + "\n" +
               "description       : " + to_str( description       ) + "\n" +
               "type              : " + to_str( type              ) + "\n" +
               "source            : " + to_str( source            ) + "\n" +
               "sourceBase        : " + to_str( sourceBase        ) + "\n" +
               "ParameterMapping  : " + to_str( ParameterMapping  ) + "\n" +
               "}";
    }

     // ParameterBinding
    std::string ParameterBinding::to_string(void) const
    {
        return "ParameterBinding { \n"
               "id                : " + to_str( id                ) + "\n" +
               "description       : " + to_str( description       ) + "\n" +
               "type              : " + to_str( type              ) + "\n" +
               "source            : " + to_str( source            ) + "\n" +
               "sourceBase        : " + to_str( sourceBase        ) + "\n" +
               "prefix            : " + to_str( prefix            ) + "\n" +
               "ParameterValues   : " + to_str( ParameterValues   ) + "\n" +
               "ParameterMapping  : " + to_str( ParameterMapping  ) + "\n" +
               "}";
    }

     // TParameterBindings
    std::string TParameterBindings::to_string(void) const
    {
        return "TParameterBindings { \n"
               "ParameterBindings  : " + to_str( ParameterBindings  ) + "\n" +
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
               "startTime    : " + to_str( startTime    ) + "\n" +
               "stopTime     : " + to_str( stopTime     ) + "\n" +
               "Annotations  : " + to_str( Annotations  ) + "\n" +
               "}";
    }

     // Connection
    std::string Connection::to_string(void) const
    {
        return "Connection { \n"
               "id                                : " + to_str( id                                ) + "\n" +
               "description                       : " + to_str( description                       ) + "\n" +
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
    std::string Connections::to_string(void) const
    {
        return "Connections { \n"
               "Connections  : " + to_str( Connections  ) + "\n" +
               "}";
    }

     // Connector
    std::string Connector::to_string(void) const
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
    std::string TConnectors::to_string(void) const
    {
        return "TConnectors { \n"
               "Connectors  : " + to_str( Connectors  ) + "\n" +
               "}";
    }

     // TComponent
    std::string TComponent::to_string(void) const
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
    std::string TSignalDictionaryReference::to_string(void) const
    {
        return "TSignalDictionaryReference { \n"
               "id                 : " + to_str( id                 ) + "\n" +
               "description        : " + to_str( description        ) + "\n" +
               "name               : " + to_str( name               ) + "\n" +
               "Connectors         : " + to_str( Connectors         ) + "\n" +
               "ElementGeometry    : " + to_str( ElementGeometry    ) + "\n" +
               "ParameterBindings  : " + to_str( ParameterBindings  ) + "\n" +
               "dictionary         : " + to_str( dictionary         ) + "\n" +
               "Annotations        : " + to_str( Annotations        ) + "\n" +
               "}";
    }

     // Elements
    std::string Elements::to_string(void) const
    {
        return "Elements { \n"
               "Components                  : " + to_str( Components                  ) + "\n" +
               "SignalDictionaryReferences  : " + to_str( SignalDictionaryReferences  ) + "\n" +
               "Systems                     : " + to_str( Systems                     ) + "\n" +
               "}";
    }

     // TSystem
    std::string TSystem::to_string(void) const
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
    std::string SystemStructureDescription::to_string(void) const
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
