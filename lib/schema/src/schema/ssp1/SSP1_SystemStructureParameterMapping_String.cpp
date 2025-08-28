

// This is a generated file, do not alter
// it is based on ssp1_ssm.toml

#include "SSP1_SystemStructureParameterMapping.hpp"
#include "common_string.hpp"

#include <string>

namespace ssp4cpp::ssp1::ssm
{
    using namespace ssp4cpp::common::str;


     // TMappingEntry
    std::string TMappingEntry::to_string(void) const
    {
        return "TMappingEntry { \n"
               "id                                : " + to_str( id                                ) + "\n" +
               "description                       : " + to_str( description                       ) + "\n" +
               "source                            : " + to_str( source                            ) + "\n" +
               "target                            : " + to_str( target                            ) + "\n" +
               "suppressUnitConversion            : " + to_str( suppressUnitConversion            ) + "\n" +
               "LinearTransformation              : " + to_str( LinearTransformation              ) + "\n" +
               "BooleanMappingTransformation      : " + to_str( BooleanMappingTransformation      ) + "\n" +
               "IntegerMappingTransformation      : " + to_str( IntegerMappingTransformation      ) + "\n" +
               "EnumerationMappingTransformation  : " + to_str( EnumerationMappingTransformation  ) + "\n" +
               "Annotations                       : " + to_str( Annotations                       ) + "\n" +
               "}";
    }

     // ParameterMapping
    std::string ParameterMapping::to_string(void) const
    {
        return "ParameterMapping { \n"
               "version                : " + to_str( version                ) + "\n" +
               "id                     : " + to_str( id                     ) + "\n" +
               "description            : " + to_str( description            ) + "\n" +
               "author                 : " + to_str( author                 ) + "\n" +
               "fileversion            : " + to_str( fileversion            ) + "\n" +
               "copyright              : " + to_str( copyright              ) + "\n" +
               "license                : " + to_str( license                ) + "\n" +
               "generationTool         : " + to_str( generationTool         ) + "\n" +
               "generationDateAndTime  : " + to_str( generationDateAndTime  ) + "\n" +
               "MappingEntry           : " + to_str( MappingEntry           ) + "\n" +
               "Annotations            : " + to_str( Annotations            ) + "\n" +
               "}";
    }

}
