#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "SystemStructureCommon.hpp"

#include "to_string.hpp"

using namespace std;

namespace ssp4cpp::ssp1::ssc
{
     // Annotation
    string Annotation::to_string(void) const
    {
        return "Annotation { \n"
               "annotation_type  : " + to_str( annotation_type  ) + "\n" +
               "any              : " + to_str( any              ) + "\n" +
               "}";
    }

     // TAnnotations
    string TAnnotations::to_string(void) const
    {
        return "TAnnotations { \n"
               "list  : " + to_str( list  ) + "\n" +
               "}";
    }

     // BooleanMapEntry
    string BooleanMapEntry::to_string(void) const
    {
        return "BooleanMapEntry { \n"
               "source  : " + to_str( source  ) + "\n" +
               "target  : " + to_str( target  ) + "\n" +
               "}";
    }

     // BooleanMappingTransformation
    string BooleanMappingTransformation::to_string(void) const
    {
        return "BooleanMappingTransformation { \n"
               "list  : " + to_str( list  ) + "\n" +
               "}";
    }

     // IntegerMapEntry
    string IntegerMapEntry::to_string(void) const
    {
        return "IntegerMapEntry { \n"
               "source  : " + to_str( source  ) + "\n" +
               "target  : " + to_str( target  ) + "\n" +
               "}";
    }

     // IntegerMappingTransformation
    string IntegerMappingTransformation::to_string(void) const
    {
        return "IntegerMappingTransformation { \n"
               "list  : " + to_str( list  ) + "\n" +
               "}";
    }

     // EnumerationMapEntry
    string EnumerationMapEntry::to_string(void) const
    {
        return "EnumerationMapEntry { \n"
               "source  : " + to_str( source  ) + "\n" +
               "target  : " + to_str( target  ) + "\n" +
               "}";
    }

     // EnumerationMappingTransformation
    string EnumerationMappingTransformation::to_string(void) const
    {
        return "EnumerationMappingTransformation { \n"
               "list  : " + to_str( list  ) + "\n" +
               "}";
    }

     // TEnumerations
    string TEnumerations::to_string(void) const
    {
        return "TEnumerations { \n"

               "}";
    }

     // BaseUnit
    string BaseUnit::to_string(void) const
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

     // TUnits
    string TUnits::to_string(void) const
    {
        return "TUnits { \n"
               "id           : " + to_str( id           ) + "\n" +
               "description  : " + to_str( description  ) + "\n" +
               "name         : " + to_str( name         ) + "\n" +
               "baseUnit     : " + to_str( baseUnit     ) + "\n" +
               "annotations  : " + to_str( annotations  ) + "\n" +
               "}";
    }

     // GTypeReal
    string GTypeReal::to_string(void) const
    {
        return "GTypeReal { \n"
               "unit  : " + to_str( unit  ) + "\n" +
               "}";
    }

     // GTypeInteger
    string GTypeInteger::to_string(void) const
    {
        return "GTypeInteger { \n"

               "}";
    }

     // GTypeBoolean
    string GTypeBoolean::to_string(void) const
    {
        return "GTypeBoolean { \n"

               "}";
    }

     // GTypeString
    string GTypeString::to_string(void) const
    {
        return "GTypeString { \n"

               "}";
    }

     // GTypeEnumeration
    string GTypeEnumeration::to_string(void) const
    {
        return "GTypeEnumeration { \n"
               "name  : " + to_str( name  ) + "\n" +
               "}";
    }

     // GTypeBinary
    string GTypeBinary::to_string(void) const
    {
        return "GTypeBinary { \n"
               "mime_type  : " + to_str( mime_type  ) + "\n" +
               "}";
    }

     // LinearTransformation
    string LinearTransformation::to_string(void) const
    {
        return "LinearTransformation { \n"
               "factor  : " + to_str( factor  ) + "\n" +
               "offset  : " + to_str( offset  ) + "\n" +
               "}";
    }


}
