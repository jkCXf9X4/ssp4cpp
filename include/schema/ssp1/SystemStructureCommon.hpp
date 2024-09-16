#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include <sstream>

// Templates
template <typename T>
std::string print_optional(const std::optional<T> &opt)
{
    std::stringstream ss;
    if (opt)
    {
        ss << *opt << std::endl;
    }
    else
    {
        ss << "null" << std::endl;
    }
    return ss.str();
}

namespace ssp4cpp::ssp1::ssc
{
    using namespace std;

    struct Annotation
    {
    
        optional<string> annotation_type;
        optional<string> any;

        friend ostream &operator<<(ostream &os, const Annotation &obj)
        {
            os << "Annotation(annotation_type: " << obj.annotation_type.value_or("null")
               << ", any: " << obj.any.value_or("null") << ")";
            return os;
        }
    };

    struct TAnnotations
    {
    
        vector<Annotation> list;

        friend ostream &operator<<(ostream &os, const TAnnotations &obj)
        {
            os << "TAnnotations { \n";
            for (const auto &i : obj.list)
            {
                os << i << endl;
            }
            os << " }" << endl;
            return os;
        }
    };

    struct BooleanMapEntry
    {
    
        bool source;
        bool target;

        friend ostream &operator<<(ostream &os, const BooleanMapEntry &obj)
        {
            os << "BooleanMapEntry(source: " << obj.source << ", target: " << obj.target << ")";
            return os;
        }
    };

    struct BooleanMappingTransformation
    {
    
        vector<BooleanMapEntry> list;

        friend ostream &operator<<(ostream &os, const BooleanMappingTransformation &obj)
        {
            os << "BooleanMappingTransformation { \n";
            for (const auto &i : obj.list)
            {
                os << i << endl;
            }
            os << " }" << endl;
            return os;
        }
        
    };

    struct IntegerMapEntry
    {
    
        int source;
        int target;

        friend ostream &operator<<(ostream &os, const IntegerMapEntry &obj)
        {
            os << "IntegerMapEntry(source: " << obj.source << ", target: " << obj.target << ")";
            return os;
        }
    };

    struct IntegerMappingTransformation
    {
    
        vector<IntegerMapEntry> list;

        friend ostream &operator<<(ostream &os, const IntegerMappingTransformation &obj)
        {
            os << "IntegerMappingTransformation { \n";
            for (const auto &i : obj.list)
            {
                os << i << endl;
            }
            os << " }" << endl;
            return os;
        }
    };

    struct EnumerationMapEntry
    {
    
        string source;
        string target;

        friend ostream &operator<<(ostream &os, const EnumerationMapEntry &obj)
        {
            os << "EnumerationMapEntry(source: " << obj.source << ", target: " << obj.target << ")";
            return os;
        }
    };

    struct EnumerationMappingTransformation
    {
    
        vector<EnumerationMapEntry> list;

        friend ostream &operator<<(ostream &os, const EnumerationMappingTransformation &obj)
        { 
            os << "EnumerationMappingTransformation { \n";
            for (const auto &i : obj.list)
            {
                os << i << endl;
            }
            os << " }" << endl;
            return os;
        }
    };

    struct TEnumerations
    {
    
        friend ostream &operator<<(ostream &os, const TEnumerations &obj)
        {
            os << "TEnumerations()";
            return os;
        }
    };

    struct BaseUnit
    {
    
        optional<int> kg;
        optional<int> m;
        optional<int> s;
        optional<int> a;
        optional<int> k;
        optional<int> mol;
        optional<int> cd;
        optional<int> rad;
        optional<double> factor;
        optional<double> offset;

        friend ostream &operator<<(ostream &os, const BaseUnit &obj)
        {
            os << "BaseUnit(kg: " << obj.kg.value_or(0) << ", m: " << obj.m.value_or(0)
               << ", s: " << obj.s.value_or(0) << ", a: " << obj.a.value_or(0)
               << ", k: " << obj.k.value_or(0) << ", mol: " << obj.mol.value_or(0)
               << ", cd: " << obj.cd.value_or(0) << ", rad: " << obj.rad.value_or(0)
               << ", factor: " << obj.factor.value_or(0.0) << ", offset: " << obj.offset.value_or(0.0) << ")";
            return os;
        }
    };

    struct TUnits
    {
    
        optional<string> id;
        optional<string> description;
        string name;
        BaseUnit baseUnit;
        optional<TAnnotations> annotations;

        friend ostream &operator<<(ostream &os, const TUnits &obj)
        {
            os << "TUnits(id: " << obj.id.value_or("null") << ", description: " << obj.description.value_or("null")
               << ", name: " << obj.name << ", baseUnit: " << obj.baseUnit
               << ", annotations: \n" << print_optional(obj.annotations) << ")";
            return os;
        }
    };

    struct GTypeReal
    {
    
        optional<string> unit;

        friend ostream &operator<<(ostream &os, const GTypeReal &obj)
        {
            os << "GTypeReal(unit: " << obj.unit.value_or("null") << ")";
            return os;
        }
    };

    struct GTypeInteger
    {
    
        friend ostream &operator<<(ostream &os, const GTypeInteger &obj)
        {
            os << "GTypeInteger()";
            return os;
        }
    };

    struct GTypeBoolean
    {
    
        friend ostream &operator<<(ostream &os, const GTypeBoolean &obj)
        {
            os << "GTypeBoolean()";
            return os;
        }
    };

    struct GTypeString
    {
    
        friend ostream &operator<<(ostream &os, const GTypeString &obj)
        {
            os << "GTypeString()";
            return os;
        }
    };

    struct GTypeEnumeration
    {
    
        optional<string> name;

        friend ostream &operator<<(ostream &os, const GTypeEnumeration &obj)
        {
            os << "GTypeEnumeration(name: " << obj.name.value_or("null") << ")";
            return os;
        }
    };

    struct GTypeBinary
    {
    
        optional<string> mime_type;

        friend ostream &operator<<(ostream &os, const GTypeBinary &obj)
        {
            os << "GTypeBinary(mime_type: " << obj.mime_type.value_or("null") << ")";
            return os;
        }
    };

    struct LinearTransformation
    {
    
        optional<double> factor;
        optional<double> offset;

        friend ostream &operator<<(ostream &os, const LinearTransformation &obj)
        {
            os << "LinearTransformation(factor: " << obj.factor.value_or(0.0)
               << ", offset: " << obj.offset.value_or(0.0) << ")";
            return os;
        }
    };
}