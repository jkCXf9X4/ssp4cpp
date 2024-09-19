#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "SSP_Enums.hpp"

namespace ssp4cpp::ssp1::ssc
{

    class Annotation
    {
    public:
        optional<string> annotation_type;
        optional<string> any;
    };
    string to_string(const Annotation &obj);

    class TAnnotations
    {
    public:
        vector<Annotation> list;
    };
    string to_string(const TAnnotations &obj);

    class BooleanMapEntry
    {
    public:
        bool source;
        bool target;
    };
    string to_string(const BooleanMapEntry &obj);

    class BooleanMappingTransformation
    {
    public:
        vector<BooleanMapEntry> list;
    };
    string to_string(const BooleanMappingTransformation &obj);

    class IntegerMapEntry
    {
    public:
        int source;
        int target;
    };
    string to_string(const IntegerMapEntry &obj);

    class IntegerMappingTransformation
    {
    public:
        vector<IntegerMapEntry> list;
    };
    string to_string(const IntegerMappingTransformation &obj);

    class EnumerationMapEntry
    {
    public:
        string source;
        string target;
    };
    string to_string(const EnumerationMapEntry &obj);

    class EnumerationMappingTransformation
    {
    public:
        vector<EnumerationMapEntry> list;
    };
    string to_string(const EnumerationMappingTransformation &obj);

    class TEnumerations
    {
    public:

    };
    string to_string(const TEnumerations &obj);

    class BaseUnit
    {
    public:
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
    };
    string to_string(const BaseUnit &obj);

    class TUnits
    {
    public:
        optional<string> id;
        optional<string> description;
        string name;
        BaseUnit baseUnit;
        optional<TAnnotations> annotations;
    };
    string to_string(const TUnits &obj);

    class GTypeReal
    {
    public:
        optional<string> unit;
    };
    string to_string(const GTypeReal &obj);

    class GTypeInteger
    {
    public:

    };
    string to_string(const GTypeInteger &obj);

    class GTypeBoolean
    {
    public:

    };
    string to_string(const GTypeBoolean &obj);

    class GTypeString
    {
    public:

    };
    string to_string(const GTypeString &obj);

    class GTypeEnumeration
    {
    public:
        optional<string> name;
    };
    string to_string(const GTypeEnumeration &obj);

    class GTypeBinary
    {
    public:
        optional<string> mime_type;
    };
    string to_string(const GTypeBinary &obj);

    class LinearTransformation
    {
    public:
        optional<double> factor;
        optional<double> offset;
    };
    string to_string(const LinearTransformation &obj);

}
