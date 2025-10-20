

// This is a generated file, do not alter
// it is based on ssp1_ssc.toml

#include "SSP1_SystemStructureCommon.hpp"
#include "utils/string.hpp"

#include <string>

namespace ssp4cpp::ssp1::ssc
{
    using namespace utils::str;


     // Annotation
    std::string Annotation::to_string(void) const
    {
        return "Annotation { \n"
               "type  : " + to_str( type  ) + "\n" +
               "any   : " + to_str( any   ) + "\n" +
               "}";
    }

     // TAnnotations
    std::string TAnnotations::to_string(void) const
    {
        return "TAnnotations { \n"
               "Annotations  : " + to_str( Annotations  ) + "\n" +
               "}";
    }

     // LinearTransformation
    std::string LinearTransformation::to_string(void) const
    {
        return "LinearTransformation { \n"
               "factor  : " + to_str( factor  ) + "\n" +
               "offset  : " + to_str( offset  ) + "\n" +
               "}";
    }

     // BooleanMapEntry
    std::string BooleanMapEntry::to_string(void) const
    {
        return "BooleanMapEntry { \n"
               "source  : " + to_str( source  ) + "\n" +
               "target  : " + to_str( target  ) + "\n" +
               "}";
    }

     // BooleanMappingTransformation
    std::string BooleanMappingTransformation::to_string(void) const
    {
        return "BooleanMappingTransformation { \n"
               "MapEntrys  : " + to_str( MapEntrys  ) + "\n" +
               "}";
    }

     // IntegerMapEntry
    std::string IntegerMapEntry::to_string(void) const
    {
        return "IntegerMapEntry { \n"
               "source  : " + to_str( source  ) + "\n" +
               "target  : " + to_str( target  ) + "\n" +
               "}";
    }

     // IntegerMappingTransformation
    std::string IntegerMappingTransformation::to_string(void) const
    {
        return "IntegerMappingTransformation { \n"
               "MapEntrys  : " + to_str( MapEntrys  ) + "\n" +
               "}";
    }

     // EnumerationMapEntry
    std::string EnumerationMapEntry::to_string(void) const
    {
        return "EnumerationMapEntry { \n"
               "source  : " + to_str( source  ) + "\n" +
               "target  : " + to_str( target  ) + "\n" +
               "}";
    }

     // EnumerationMappingTransformation
    std::string EnumerationMappingTransformation::to_string(void) const
    {
        return "EnumerationMappingTransformation { \n"
               "MapEntrys  : " + to_str( MapEntrys  ) + "\n" +
               "}";
    }

     // Item
    std::string Item::to_string(void) const
    {
        return "Item { \n"
               "name   : " + to_str( name   ) + "\n" +
               "value  : " + to_str( value  ) + "\n" +
               "}";
    }

     // TEnumeration
    std::string TEnumeration::to_string(void) const
    {
        return "TEnumeration { \n"
               "id           : " + to_str( id           ) + "\n" +
               "description  : " + to_str( description  ) + "\n" +
               "name         : " + to_str( name         ) + "\n" +
               "Item         : " + to_str( Item         ) + "\n" +
               "Annotations  : " + to_str( Annotations  ) + "\n" +
               "}";
    }

     // TEnumerations
    std::string TEnumerations::to_string(void) const
    {
        return "TEnumerations { \n"
               "Enumerations  : " + to_str( Enumerations  ) + "\n" +
               "}";
    }

     // BaseUnit
    std::string BaseUnit::to_string(void) const
    {
        return "BaseUnit { \n"
               "kg      : " + to_str( kg      ) + "\n" +
               "m       : " + to_str( m       ) + "\n" +
               "s       : " + to_str( s       ) + "\n" +
               "a       : " + to_str( a       ) + "\n" +
               "k       : " + to_str( k       ) + "\n" +
               "mol     : " + to_str( mol     ) + "\n" +
               "cd      : " + to_str( cd      ) + "\n" +
               "rad     : " + to_str( rad     ) + "\n" +
               "factor  : " + to_str( factor  ) + "\n" +
               "offset  : " + to_str( offset  ) + "\n" +
               "}";
    }

     // TUnit
    std::string TUnit::to_string(void) const
    {
        return "TUnit { \n"
               "id           : " + to_str( id           ) + "\n" +
               "description  : " + to_str( description  ) + "\n" +
               "name         : " + to_str( name         ) + "\n" +
               "BaseUnit     : " + to_str( BaseUnit     ) + "\n" +
               "Annotations  : " + to_str( Annotations  ) + "\n" +
               "}";
    }

     // TUnits
    std::string TUnits::to_string(void) const
    {
        return "TUnits { \n"
               "Units  : " + to_str( Units  ) + "\n" +
               "}";
    }

     // GTypeReal
    std::string GTypeReal::to_string(void) const
    {
        return "GTypeReal { \n"
               "unit  : " + to_str( unit  ) + "\n" +
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
               "name  : " + to_str( name  ) + "\n" +
               "}";
    }

     // GTypeBinary
    std::string GTypeBinary::to_string(void) const
    {
        return "GTypeBinary { \n"
               "mime_type  : " + to_str( mime_type  ) + "\n" +
               "}";
    }

}
