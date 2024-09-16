#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>

namespace ssp4cpp::ssp1::ssc
{
    using namespace std;

    struct Annotation
    {
        optional<string> annotation_type;
        optional<string> any;
    };
    string to_string(const Annotation &obj);

    struct TAnnotations
    {
        vector<Annotation> list;
    };
    string to_string(const TAnnotations &obj);

    struct BooleanMapEntry
    {
        bool source;
        bool target;
    };
    string to_string(const BooleanMapEntry &obj);

    struct BooleanMappingTransformation
    {
        vector<BooleanMapEntry> list;
    };
    string to_string(const BooleanMappingTransformation &obj);

    struct IntegerMapEntry
    {
        int source;
        int target;
    };
    string to_string(const IntegerMapEntry &obj);

    struct IntegerMappingTransformation
    {
        vector<IntegerMapEntry> list;
    };
    string to_string(const IntegerMappingTransformation &obj);

    struct EnumerationMapEntry
    {
        string source;
        string target;
    };
    string to_string(const EnumerationMapEntry &obj);

    struct EnumerationMappingTransformation
    {
        vector<EnumerationMapEntry> list;
    };
    string to_string(const EnumerationMappingTransformation &obj);

    struct TEnumerations
    {
    };
    string to_string(const TEnumerations &);

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
    };
    string to_string(const BaseUnit &obj);

    struct TUnits
    {
        optional<string> id;
        optional<string> description;
        string name;
        BaseUnit baseUnit;
        optional<TAnnotations> annotations;
    };
    string to_string(const TUnits &obj);

    struct GTypeReal
    {
        optional<string> unit;
    };
    string to_string(const GTypeReal &obj);

    struct GTypeInteger
    {
    };
    string to_string(const GTypeInteger &);

    struct GTypeBoolean
    {
    };
    string to_string(const GTypeBoolean &);

    struct GTypeString
    {
    };
    string to_string(const GTypeString &);

    struct GTypeEnumeration
    {
        optional<string> name;
    };
    string to_string(const GTypeEnumeration &obj);

    struct GTypeBinary
    {
        optional<string> mime_type;
    };
    string to_string(const GTypeBinary &obj);

    struct LinearTransformation
    {
        optional<double> factor;
        optional<double> offset;
    };
    string to_string(const LinearTransformation &obj);
}