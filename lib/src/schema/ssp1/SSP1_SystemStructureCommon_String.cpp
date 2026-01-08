

// This is a generated file, do not alter
// it is based on ssp1_ssc.toml

#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureCommon.hpp"
#include "ssp4cpp/utils/string.hpp"

#include <string>

namespace ssp4cpp::ssp1::ssc
{


     // Annotation
    std::string Annotation::to_string(void) const
    {
        return "Annotation { \n"
               "type  : " + utils::str::to_string( type  ) + "\n" +
               "any   : " + utils::str::to_string( any   ) + "\n" +
               "}";
    }

     // TAnnotations
    std::string TAnnotations::to_string(void) const
    {
        return "TAnnotations { \n"
               "Annotations  : " + utils::str::to_string( Annotations  ) + "\n" +
               "}";
    }

     // LinearTransformation
    std::string LinearTransformation::to_string(void) const
    {
        return "LinearTransformation { \n"
               "factor  : " + utils::str::to_string( factor  ) + "\n" +
               "offset  : " + utils::str::to_string( offset  ) + "\n" +
               "}";
    }

     // BooleanMapEntry
    std::string BooleanMapEntry::to_string(void) const
    {
        return "BooleanMapEntry { \n"
               "source  : " + utils::str::to_string( source  ) + "\n" +
               "target  : " + utils::str::to_string( target  ) + "\n" +
               "}";
    }

     // BooleanMappingTransformation
    std::string BooleanMappingTransformation::to_string(void) const
    {
        return "BooleanMappingTransformation { \n"
               "MapEntrys  : " + utils::str::to_string( MapEntrys  ) + "\n" +
               "}";
    }

     // IntegerMapEntry
    std::string IntegerMapEntry::to_string(void) const
    {
        return "IntegerMapEntry { \n"
               "source  : " + utils::str::to_string( source  ) + "\n" +
               "target  : " + utils::str::to_string( target  ) + "\n" +
               "}";
    }

     // IntegerMappingTransformation
    std::string IntegerMappingTransformation::to_string(void) const
    {
        return "IntegerMappingTransformation { \n"
               "MapEntrys  : " + utils::str::to_string( MapEntrys  ) + "\n" +
               "}";
    }

     // EnumerationMapEntry
    std::string EnumerationMapEntry::to_string(void) const
    {
        return "EnumerationMapEntry { \n"
               "source  : " + utils::str::to_string( source  ) + "\n" +
               "target  : " + utils::str::to_string( target  ) + "\n" +
               "}";
    }

     // EnumerationMappingTransformation
    std::string EnumerationMappingTransformation::to_string(void) const
    {
        return "EnumerationMappingTransformation { \n"
               "MapEntrys  : " + utils::str::to_string( MapEntrys  ) + "\n" +
               "}";
    }

     // Item
    std::string Item::to_string(void) const
    {
        return "Item { \n"
               "name   : " + utils::str::to_string( name   ) + "\n" +
               "value  : " + utils::str::to_string( value  ) + "\n" +
               "}";
    }

     // TEnumeration
    std::string TEnumeration::to_string(void) const
    {
        return "TEnumeration { \n"
               "id           : " + utils::str::to_string( id           ) + "\n" +
               "description  : " + utils::str::to_string( description  ) + "\n" +
               "name         : " + utils::str::to_string( name         ) + "\n" +
               "Item         : " + utils::str::to_string( Item         ) + "\n" +
               "Annotations  : " + utils::str::to_string( Annotations  ) + "\n" +
               "}";
    }

     // TEnumerations
    std::string TEnumerations::to_string(void) const
    {
        return "TEnumerations { \n"
               "Enumerations  : " + utils::str::to_string( Enumerations  ) + "\n" +
               "}";
    }

     // BaseUnit
    std::string BaseUnit::to_string(void) const
    {
        return "BaseUnit { \n"
               "kg      : " + utils::str::to_string( kg      ) + "\n" +
               "m       : " + utils::str::to_string( m       ) + "\n" +
               "s       : " + utils::str::to_string( s       ) + "\n" +
               "a       : " + utils::str::to_string( a       ) + "\n" +
               "k       : " + utils::str::to_string( k       ) + "\n" +
               "mol     : " + utils::str::to_string( mol     ) + "\n" +
               "cd      : " + utils::str::to_string( cd      ) + "\n" +
               "rad     : " + utils::str::to_string( rad     ) + "\n" +
               "factor  : " + utils::str::to_string( factor  ) + "\n" +
               "offset  : " + utils::str::to_string( offset  ) + "\n" +
               "}";
    }

     // TUnit
    std::string TUnit::to_string(void) const
    {
        return "TUnit { \n"
               "id           : " + utils::str::to_string( id           ) + "\n" +
               "description  : " + utils::str::to_string( description  ) + "\n" +
               "name         : " + utils::str::to_string( name         ) + "\n" +
               "BaseUnit     : " + utils::str::to_string( BaseUnit     ) + "\n" +
               "Annotations  : " + utils::str::to_string( Annotations  ) + "\n" +
               "}";
    }

     // TUnits
    std::string TUnits::to_string(void) const
    {
        return "TUnits { \n"
               "Units  : " + utils::str::to_string( Units  ) + "\n" +
               "}";
    }

     // GTypeReal
    std::string GTypeReal::to_string(void) const
    {
        return "GTypeReal { \n"
               "unit  : " + utils::str::to_string( unit  ) + "\n" +
               "}";
    }

     // GTypeInteger
    std::string GTypeInteger::to_string(void) const
    {
        return "GTypeInteger { \n"

               "}";
    }

     // GTypeBoolean
    std::string GTypeBoolean::to_string(void) const
    {
        return "GTypeBoolean { \n"

               "}";
    }

     // GTypeString
    std::string GTypeString::to_string(void) const
    {
        return "GTypeString { \n"

               "}";
    }

     // GTypeEnumeration
    std::string GTypeEnumeration::to_string(void) const
    {
        return "GTypeEnumeration { \n"
               "name  : " + utils::str::to_string( name  ) + "\n" +
               "}";
    }

     // GTypeBinary
    std::string GTypeBinary::to_string(void) const
    {
        return "GTypeBinary { \n"
               "mime_type  : " + utils::str::to_string( mime_type  ) + "\n" +
               "}";
    }

}
