

// This is a generated file, do not alter
// it is based on ssp1_ssv.toml

#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureParameterValues.hpp"
#include "ssp4cpp/utils/string.hpp"

#include <string>

namespace ssp4cpp::ssp1::ssv
{


     // Real
    std::string Real::to_string(void) const
    {
        return "Real { \n"
               "value  : " + utils::str::to_string( value  ) + "\n" +
               "unit   : " + utils::str::to_string( unit   ) + "\n" +
               "}";
    }

     // Integer
    std::string Integer::to_string(void) const
    {
        return "Integer { \n"
               "value  : " + utils::str::to_string( value  ) + "\n" +
               "}";
    }

     // Boolean
    std::string Boolean::to_string(void) const
    {
        return "Boolean { \n"
               "value  : " + utils::str::to_string( value  ) + "\n" +
               "}";
    }

     // String
    std::string String::to_string(void) const
    {
        return "String { \n"
               "value  : " + utils::str::to_string( value  ) + "\n" +
               "}";
    }

     // Enumeration
    std::string Enumeration::to_string(void) const
    {
        return "Enumeration { \n"
               "value  : " + utils::str::to_string( value  ) + "\n" +
               "name   : " + utils::str::to_string( name   ) + "\n" +
               "}";
    }

     // Binary
    std::string Binary::to_string(void) const
    {
        return "Binary { \n"
               "value      : " + utils::str::to_string( value      ) + "\n" +
               "mime_type  : " + utils::str::to_string( mime_type  ) + "\n" +
               "}";
    }

     // TParameter
    std::string TParameter::to_string(void) const
    {
        return "TParameter { \n"
               "id           : " + utils::str::to_string( id           ) + "\n" +
               "description  : " + utils::str::to_string( description  ) + "\n" +
               "name         : " + utils::str::to_string( name         ) + "\n" +
               "Real         : " + utils::str::to_string( Real         ) + "\n" +
               "Integer      : " + utils::str::to_string( Integer      ) + "\n" +
               "Boolean      : " + utils::str::to_string( Boolean      ) + "\n" +
               "String       : " + utils::str::to_string( String       ) + "\n" +
               "Enumeration  : " + utils::str::to_string( Enumeration  ) + "\n" +
               "Binary       : " + utils::str::to_string( Binary       ) + "\n" +
               "Annotations  : " + utils::str::to_string( Annotations  ) + "\n" +
               "}";
    }

     // TParameters
    std::string TParameters::to_string(void) const
    {
        return "TParameters { \n"
               "Parameters  : " + utils::str::to_string( Parameters  ) + "\n" +
               "}";
    }

     // ParameterSet
    std::string ParameterSet::to_string(void) const
    {
        return "ParameterSet { \n"
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
               "Parameters             : " + utils::str::to_string( Parameters             ) + "\n" +
               "Enumerations           : " + utils::str::to_string( Enumerations           ) + "\n" +
               "Units                  : " + utils::str::to_string( Units                  ) + "\n" +
               "Annotations            : " + utils::str::to_string( Annotations            ) + "\n" +
               "}";
    }

}
