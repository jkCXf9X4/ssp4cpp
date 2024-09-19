#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "SystemStructureCommon.hpp"

#include "print_misc.hpp"

using namespace std;

namespace ssp4cpp::ssp1::ssc
{     
    // Annotation
    string to_string(const Annotation &obj)
    {
        return "Annotation { \n"
               "annotation_type   : " + obj.annotation_type.value_or("null")                    + "\n" +
               "any               : " + obj.any.value_or("null")                                + "\n" +
               "}";
    }
    string to_string(const optional<Annotation> &obj) { return to_string_optional(obj); }
    string to_string(const vector<Annotation> &obj) { return to_string_vector(obj); }

     // TAnnotations
    string to_string(const TAnnotations &obj)
    {
        return "TAnnotations { \n"
               "list   : " + to_string_vector(obj.list    ) + "\n" +
               "}";
    }
    string to_string(const optional<TAnnotations> &obj) { return to_string_optional(obj); }
    string to_string(const vector<TAnnotations> &obj) { return to_string_vector(obj); }

     // BooleanMapEntry
    string to_string(const BooleanMapEntry &obj)
    {
        return "BooleanMapEntry { \n"
               "source   : " + std::to_string(obj.source )                         + "\n" +
               "target   : " + std::to_string(obj.target )                         + "\n" +
               "}";
    }
    string to_string(const optional<BooleanMapEntry> &obj) { return to_string_optional(obj); }
    string to_string(const vector<BooleanMapEntry> &obj) { return to_string_vector(obj); }

     // BooleanMappingTransformation
    string to_string(const BooleanMappingTransformation &obj)
    {
        return "BooleanMappingTransformation { \n"
               "list   : " + to_string_vector(obj.list    ) + "\n" +
               "}";
    }
    string to_string(const optional<BooleanMappingTransformation> &obj) { return to_string_optional(obj); }
    string to_string(const vector<BooleanMappingTransformation> &obj) { return to_string_vector(obj); }

     // IntegerMapEntry
    string to_string(const IntegerMapEntry &obj)
    {
        return "IntegerMapEntry { \n"
               "source   : " + std::to_string(obj.source )                         + "\n" +
               "target   : " + std::to_string(obj.target )                         + "\n" +
               "}";
    }
    string to_string(const optional<IntegerMapEntry> &obj) { return to_string_optional(obj); }
    string to_string(const vector<IntegerMapEntry> &obj) { return to_string_vector(obj); }

     // IntegerMappingTransformation
    string to_string(const IntegerMappingTransformation &obj)
    {
        return "IntegerMappingTransformation { \n"
               "list   : " + to_string_vector(obj.list    ) + "\n" +
               "}";
    }
    string to_string(const optional<IntegerMappingTransformation> &obj) { return to_string_optional(obj); }
    string to_string(const vector<IntegerMappingTransformation> &obj) { return to_string_vector(obj); }

     // EnumerationMapEntry
    string to_string(const EnumerationMapEntry &obj)
    {
        return "EnumerationMapEntry { \n"
               "source   : " + obj.source                                     + "\n" +
               "target   : " + obj.target                                     + "\n" +
               "}";
    }
    string to_string(const optional<EnumerationMapEntry> &obj) { return to_string_optional(obj); }
    string to_string(const vector<EnumerationMapEntry> &obj) { return to_string_vector(obj); }

     // EnumerationMappingTransformation
    string to_string(const EnumerationMappingTransformation &obj)
    {
        return "EnumerationMappingTransformation { \n"
               "list   : " + to_string_vector(obj.list    ) + "\n" +
               "}";
    }
    string to_string(const optional<EnumerationMappingTransformation> &obj) { return to_string_optional(obj); }
    string to_string(const vector<EnumerationMappingTransformation> &obj) { return to_string_vector(obj); }

     // TEnumerations
    string to_string(const TEnumerations &obj)
    {
        return "TEnumerations { \n"

               "}";
    }
    string to_string(const optional<TEnumerations> &obj) { return to_string_optional(obj); }
    string to_string(const vector<TEnumerations> &obj) { return to_string_vector(obj); }

     // BaseUnit
    string to_string(const BaseUnit &obj)
    {
        return "BaseUnit { \n"
               "kg       : " + std::to_string( obj.kg.value_or(0) )           + "\n" +
               "m        : " + std::to_string( obj.m.value_or(0) )            + "\n" +
               "s        : " + std::to_string( obj.s.value_or(0) )            + "\n" +
               "a        : " + std::to_string( obj.a.value_or(0) )            + "\n" +
               "k        : " + std::to_string( obj.k.value_or(0) )            + "\n" +
               "mol      : " + std::to_string( obj.mol.value_or(0) )          + "\n" +
               "cd       : " + std::to_string( obj.cd.value_or(0) )           + "\n" +
               "rad      : " + std::to_string( obj.rad.value_or(0) )          + "\n" +
               "factor   : " + std::to_string( obj.factor.value_or(0.0) )     + "\n" +
               "offset   : " + std::to_string( obj.offset.value_or(0.0) )     + "\n" +
               "}";
    }
    string to_string(const optional<BaseUnit> &obj) { return to_string_optional(obj); }
    string to_string(const vector<BaseUnit> &obj) { return to_string_vector(obj); }

     // TUnits
    string to_string(const TUnits &obj)
    {
        return "TUnits { \n"
               "id            : " + obj.id.value_or("null")                             + "\n" +
               "description   : " + obj.description.value_or("null")                    + "\n" +
               "name          : " + obj.name                                            + "\n" +
               "baseUnit      : " + to_string(obj.baseUnit )                            + "\n" +
               "annotations   : " + to_string( obj.annotations )                        + "\n" +
               "}";
    }
    string to_string(const optional<TUnits> &obj) { return to_string_optional(obj); }
    string to_string(const vector<TUnits> &obj) { return to_string_vector(obj); }

     // GTypeReal
    string to_string(const GTypeReal &obj)
    {
        return "GTypeReal { \n"
               "unit   : " + obj.unit.value_or("null")                    + "\n" +
               "}";
    }
    string to_string(const optional<GTypeReal> &obj) { return to_string_optional(obj); }
    string to_string(const vector<GTypeReal> &obj) { return to_string_vector(obj); }

     // GTypeInteger
    string to_string(const GTypeInteger &obj)
    {
        return "GTypeInteger { \n"

               "}";
    }
    string to_string(const optional<GTypeInteger> &obj) { return to_string_optional(obj); }
    string to_string(const vector<GTypeInteger> &obj) { return to_string_vector(obj); }

     // GTypeBoolean
    string to_string(const GTypeBoolean &obj)
    {
        return "GTypeBoolean { \n"

               "}";
    }
    string to_string(const optional<GTypeBoolean> &obj) { return to_string_optional(obj); }
    string to_string(const vector<GTypeBoolean> &obj) { return to_string_vector(obj); }

     // GTypeString
    string to_string(const GTypeString &obj)
    {
        return "GTypeString { \n"

               "}";
    }
    string to_string(const optional<GTypeString> &obj) { return to_string_optional(obj); }
    string to_string(const vector<GTypeString> &obj) { return to_string_vector(obj); }

     // GTypeEnumeration
    string to_string(const GTypeEnumeration &obj)
    {
        return "GTypeEnumeration { \n"
               "name   : " + obj.name.value_or("null")                    + "\n" +
               "}";
    }
    string to_string(const optional<GTypeEnumeration> &obj) { return to_string_optional(obj); }
    string to_string(const vector<GTypeEnumeration> &obj) { return to_string_vector(obj); }

     // GTypeBinary
    string to_string(const GTypeBinary &obj)
    {
        return "GTypeBinary { \n"
               "mime_type   : " + obj.mime_type.value_or("null")                    + "\n" +
               "}";
    }
    string to_string(const optional<GTypeBinary> &obj) { return to_string_optional(obj); }
    string to_string(const vector<GTypeBinary> &obj) { return to_string_vector(obj); }

     // LinearTransformation
    string to_string(const LinearTransformation &obj)
    {
        return "LinearTransformation { \n"
               "factor   : " + std::to_string( obj.factor.value_or(0.0) )     + "\n" +
               "offset   : " + std::to_string( obj.offset.value_or(0.0) )     + "\n" +
               "}";
    }
    string to_string(const optional<LinearTransformation> &obj) { return to_string_optional(obj); }
    string to_string(const vector<LinearTransformation> &obj) { return to_string_vector(obj); }

}