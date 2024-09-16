#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "SystemStructureCommon.hpp"
#include "print_misc.hpp"

namespace ssp4cpp::ssp1::ssc
{
    using namespace std;

    string to_string(const Annotation &obj)
    {
        return "Annotation(annotation_type: " + obj.annotation_type.value_or("null") +
               ", any: " + obj.any.value_or("null") + ")";
    }

    string to_string(const TAnnotations &obj)
    {
        string result = "TAnnotations { \n";
        for (const auto &i : obj.list)
        {
            result += to_string(i) + "\n";
        }
        result += " }";
        return result;
    }

    string to_string(const BooleanMapEntry &obj)
    {
        return "BooleanMapEntry(source: " + std::to_string(obj.source) +
               ", target: " + std::to_string(obj.target) + ")";
    }

    string to_string(const BooleanMappingTransformation &obj)
    {
        string result = "BooleanMappingTransformation { \n";
        for (const auto &i : obj.list)
        {
            result += to_string(i) + "\n";
        }
        result += " }";
        return result;
    }

    string to_string(const IntegerMapEntry &obj)
    {
        return "IntegerMapEntry(source: " + std::to_string(obj.source) +
               ", target: " + std::to_string(obj.target) + ")";
    }

    string to_string(const IntegerMappingTransformation &obj)
    {
        string result = "IntegerMappingTransformation { \n";
        for (const auto &i : obj.list)
        {
            result += to_string(i) + "\n";
        }
        result += " }";
        return result;
    }

    string to_string(const EnumerationMapEntry &obj)
    {
        return "EnumerationMapEntry(source: " + obj.source +
               ", target: " + obj.target + ")";
    }

    string to_string(const EnumerationMappingTransformation &obj)
    {
        string result = "EnumerationMappingTransformation { \n";
        for (const auto &i : obj.list)
        {
            result += to_string(i) + "\n";
        }
        result += " }";
        return result;
    }

    string to_string(const TEnumerations &)
    {
        return "TEnumerations()";
    }

    string to_string(const BaseUnit &obj)
    {
        return "BaseUnit(kg: " + std::to_string(obj.kg.value_or(0)) +
               ", m: " + std::to_string(obj.m.value_or(0)) +
               ", s: " + std::to_string(obj.s.value_or(0)) +
               ", a: " + std::to_string(obj.a.value_or(0)) +
               ", k: " + std::to_string(obj.k.value_or(0)) +
               ", mol: " + std::to_string(obj.mol.value_or(0)) +
               ", cd: " + std::to_string(obj.cd.value_or(0)) +
               ", rad: " + std::to_string(obj.rad.value_or(0)) +
               ", factor: " + std::to_string(obj.factor.value_or(0.0)) +
               ", offset: " + std::to_string(obj.offset.value_or(0.0)) + ")";
    }

    string to_string(const TUnits &obj)
    {
        return "TUnits(id: " + obj.id.value_or("null") +
               ", description: " + obj.description.value_or("null") +
               ", name: " + obj.name +
               ", baseUnit: " + to_string(obj.baseUnit) +
               ", annotations: \n" + to_string_optional(obj.annotations) + ")";
    }

    string to_string(const GTypeReal &obj)
    {
        return "GTypeReal(unit: " + obj.unit.value_or("null") + ")";
    }

    string to_string(const GTypeInteger &)
    {
        return "GTypeInteger()";
    }

    string to_string(const GTypeBoolean &)
    {
        return "GTypeBoolean()";
    }

    string to_string(const GTypeString &)
    {
        return "GTypeString()";
    }

    string to_string(const GTypeEnumeration &obj)
    {
        return "GTypeEnumeration(name: " + obj.name.value_or("null") + ")";
    }

    string to_string(const GTypeBinary &obj)
    {
        return "GTypeBinary(mime_type: " + obj.mime_type.value_or("null") + ")";
    }

    string to_string(const LinearTransformation &obj)
    {
        return "LinearTransformation(factor: " + std::to_string(obj.factor.value_or(0.0)) +
               ", offset: " + std::to_string(obj.offset.value_or(0.0)) + ")";
    }

}