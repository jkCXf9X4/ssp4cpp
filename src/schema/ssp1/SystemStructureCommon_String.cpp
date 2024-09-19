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
    string to_string(const Annotation &obj)
    {
        return "Annotation { \n"
               "annotation_type   : " + to_str( obj.annotation_type )                           + "\n" +
               "any               : " + to_str( obj.any )                                       + "\n" +
               "}";
    }

     // TAnnotations
    string to_string(const TAnnotations &obj)
    {
        return "TAnnotations { \n"
               "list   : " + to_str(obj.list    ) + "\n" +
               "}";
    }

     // BooleanMapEntry
    string to_string(const BooleanMapEntry &obj)
    {
        return "BooleanMapEntry { \n"
               "source   : " + to_str( obj.source )                           + "\n" +
               "target   : " + to_str( obj.target )                           + "\n" +
               "}";
    }

     // BooleanMappingTransformation
    string to_string(const BooleanMappingTransformation &obj)
    {
        return "BooleanMappingTransformation { \n"
               "list   : " + to_str(obj.list    ) + "\n" +
               "}";
    }

     // IntegerMapEntry
    string to_string(const IntegerMapEntry &obj)
    {
        return "IntegerMapEntry { \n"
               "source   : " + to_str( obj.source )                           + "\n" +
               "target   : " + to_str( obj.target )                           + "\n" +
               "}";
    }

     // IntegerMappingTransformation
    string to_string(const IntegerMappingTransformation &obj)
    {
        return "IntegerMappingTransformation { \n"
               "list   : " + to_str(obj.list    ) + "\n" +
               "}";
    }

     // EnumerationMapEntry
    string to_string(const EnumerationMapEntry &obj)
    {
        return "EnumerationMapEntry { \n"
               "source   : " + to_str( obj.source )                           + "\n" +
               "target   : " + to_str( obj.target )                           + "\n" +
               "}";
    }

     // EnumerationMappingTransformation
    string to_string(const EnumerationMappingTransformation &obj)
    {
        return "EnumerationMappingTransformation { \n"
               "list   : " + to_str(obj.list    ) + "\n" +
               "}";
    }

     // TEnumerations
    string to_string(const TEnumerations &obj)
    {
        return "TEnumerations { \n"

               "}";
    }

     // BaseUnit
    string to_string(const BaseUnit &obj)
    {
        return "BaseUnit { \n"
               "kg       : " + to_str( obj.kg )                               + "\n" +
               "m        : " + to_str( obj.m )                                + "\n" +
               "s        : " + to_str( obj.s )                                + "\n" +
               "a        : " + to_str( obj.a )                                + "\n" +
               "k        : " + to_str( obj.k )                                + "\n" +
               "mol      : " + to_str( obj.mol )                              + "\n" +
               "cd       : " + to_str( obj.cd )                               + "\n" +
               "rad      : " + to_str( obj.rad )                              + "\n" +
               "factor   : " + to_str( obj.factor )                           + "\n" +
               "offset   : " + to_str( obj.offset )                           + "\n" +
               "}";
    }

     // TUnits
    string to_string(const TUnits &obj)
    {
        return "TUnits { \n"
               "id            : " + to_str( obj.id )                                    + "\n" +
               "description   : " + to_str( obj.description )                           + "\n" +
               "name          : " + to_str( obj.name )                                  + "\n" +
               "baseUnit      : " + to_string( obj.baseUnit )                           + "\n" +
               "annotations   : " + to_str( obj.annotations )                           + "\n" +
               "}";
    }

     // GTypeReal
    string to_string(const GTypeReal &obj)
    {
        return "GTypeReal { \n"
               "unit   : " + to_str( obj.unit )                           + "\n" +
               "}";
    }

     // GTypeInteger
    string to_string(const GTypeInteger &obj)
    {
        return "GTypeInteger { \n"

               "}";
    }

     // GTypeBoolean
    string to_string(const GTypeBoolean &obj)
    {
        return "GTypeBoolean { \n"

               "}";
    }

     // GTypeString
    string to_string(const GTypeString &obj)
    {
        return "GTypeString { \n"

               "}";
    }

     // GTypeEnumeration
    string to_string(const GTypeEnumeration &obj)
    {
        return "GTypeEnumeration { \n"
               "name   : " + to_str( obj.name )                           + "\n" +
               "}";
    }

     // GTypeBinary
    string to_string(const GTypeBinary &obj)
    {
        return "GTypeBinary { \n"
               "mime_type   : " + to_str( obj.mime_type )                           + "\n" +
               "}";
    }

     // LinearTransformation
    string to_string(const LinearTransformation &obj)
    {
        return "LinearTransformation { \n"
               "factor   : " + to_str( obj.factor )                           + "\n" +
               "offset   : " + to_str( obj.offset )                           + "\n" +
               "}";
    }


}
