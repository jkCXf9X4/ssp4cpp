

// This is a generated file, do not alter
// it is based on ssp1_ssv.toml

#include "SSP1_SystemStructureParameterValues.hpp"
#include "common_string.hpp"

#include <string>

namespace ssp4cpp::ssp1::ssv
{
    using namespace ssp4cpp::common::str;


     // Real
    std::string Real::to_string(void) const
    {
        return "Real { \n"
               "value  : " + to_str( value  ) + "\n" +
               "unit   : " + to_str( unit   ) + "\n" +
               "}";
    }

     // Integer
    std::string Integer::to_string(void) const
    {
        return "Integer { \n"
               "value  : " + to_str( value  ) + "\n" +
               "}";
    }

     // Boolean
    std::string Boolean::to_string(void) const
    {
        return "Boolean { \n"
               "value  : " + to_str( value  ) + "\n" +
               "}";
    }

     // String
    std::string String::to_string(void) const
    {
        return "String { \n"
               "value  : " + to_str( value  ) + "\n" +
               "}";
    }

     // Enumeration
    std::string Enumeration::to_string(void) const
    {
        return "Enumeration { \n"
               "value  : " + to_str( value  ) + "\n" +
               "name   : " + to_str( name   ) + "\n" +
               "}";
    }

     // Binary
    std::string Binary::to_string(void) const
    {
        return "Binary { \n"
               "value      : " + to_str( value      ) + "\n" +
               "mime_type  : " + to_str( mime_type  ) + "\n" +
               "}";
    }

     // TParameter
    std::string TParameter::to_string(void) const
    {
        return "TParameter { \n"
               "id           : " + to_str( id           ) + "\n" +
               "description  : " + to_str( description  ) + "\n" +
               "name         : " + to_str( name         ) + "\n" +
               "Real         : " + to_str( Real         ) + "\n" +
               "Integer      : " + to_str( Integer      ) + "\n" +
               "Boolean      : " + to_str( Boolean      ) + "\n" +
               "String       : " + to_str( String       ) + "\n" +
               "Enumeration  : " + to_str( Enumeration  ) + "\n" +
               "Binary       : " + to_str( Binary       ) + "\n" +
               "Annotations  : " + to_str( Annotations  ) + "\n" +
               "}";
    }

     // TParameters
    std::string TParameters::to_string(void) const
    {
        return "TParameters { \n"
               "Parameters  : " + to_str( Parameters  ) + "\n" +
               "}";
    }

     // ParameterSet
    std::string ParameterSet::to_string(void) const
    {
        return "ParameterSet { \n"
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
               "Parameters             : " + to_str( Parameters             ) + "\n" +
               "Enumerations           : " + to_str( Enumerations           ) + "\n" +
               "Units                  : " + to_str( Units                  ) + "\n" +
               "Annotations            : " + to_str( Annotations            ) + "\n" +
               "}";
    }

}
