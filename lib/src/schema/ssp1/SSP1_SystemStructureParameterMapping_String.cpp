

// This is a generated file, do not alter
// it is based on ssp1_ssm.toml

#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureParameterMapping.hpp"
#include "ssp4cpp/utils/string.hpp"

#include <string>

namespace ssp4cpp::ssp1::ssm
{


     // TMappingEntry
    std::string TMappingEntry::to_string(void) const
    {
        return "TMappingEntry { \n"
               "id                                : " + utils::str::to_string( id                                ) + "\n" +
               "description                       : " + utils::str::to_string( description                       ) + "\n" +
               "source                            : " + utils::str::to_string( source                            ) + "\n" +
               "target                            : " + utils::str::to_string( target                            ) + "\n" +
               "suppressUnitConversion            : " + utils::str::to_string( suppressUnitConversion            ) + "\n" +
               "LinearTransformation              : " + utils::str::to_string( LinearTransformation              ) + "\n" +
               "BooleanMappingTransformation      : " + utils::str::to_string( BooleanMappingTransformation      ) + "\n" +
               "IntegerMappingTransformation      : " + utils::str::to_string( IntegerMappingTransformation      ) + "\n" +
               "EnumerationMappingTransformation  : " + utils::str::to_string( EnumerationMappingTransformation  ) + "\n" +
               "Annotations                       : " + utils::str::to_string( Annotations                       ) + "\n" +
               "}";
    }

     // ParameterMapping
    std::string ParameterMapping::to_string(void) const
    {
        return "ParameterMapping { \n"
               "version                : " + utils::str::to_string( version                ) + "\n" +
               "id                     : " + utils::str::to_string( id                     ) + "\n" +
               "description            : " + utils::str::to_string( description            ) + "\n" +
               "author                 : " + utils::str::to_string( author                 ) + "\n" +
               "fileversion            : " + utils::str::to_string( fileversion            ) + "\n" +
               "copyright              : " + utils::str::to_string( copyright              ) + "\n" +
               "license                : " + utils::str::to_string( license                ) + "\n" +
               "generationTool         : " + utils::str::to_string( generationTool         ) + "\n" +
               "generationDateAndTime  : " + utils::str::to_string( generationDateAndTime  ) + "\n" +
               "MappingEntry           : " + utils::str::to_string( MappingEntry           ) + "\n" +
               "Annotations            : " + utils::str::to_string( Annotations            ) + "\n" +
               "}";
    }

}
