#pragma once

#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::ssp1::ssc
{
    using namespace std;

    // Annotation struct
    struct Annotation
    {
        optional<string> annotation_type;
        optional<string> any;
    };

    // Annotations struct
    struct TAnnotations
    {
        vector<Annotation> list;
    };

    struct BooleanMapEntry
    {
        bool source;
        bool target;
    };

    struct BooleanMappingTransformation
    {
        vector<BooleanMapEntry> list;
    };

    struct IntegerMapEntry
    {
        int source;
        int target;
    };

    struct IntegerMappingTransformation
    {
        vector<IntegerMapEntry> list;
    };

    struct EnumerationMapEntry
    {
        string source;
        string target;
    };

    struct EnumerationMappingTransformation
    {
        vector<EnumerationMapEntry> list;
    };

    // Struct definitions

    struct TEnumerations
    {
    };

    // Base unit struct
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

    // Units struct
    struct TUnits
    {
        optional<string> id;
        optional<string> description;
        string name;
        BaseUnit baseUnit;
        optional<TAnnotations> annotations;
    };

    // GType structs
    struct GTypeReal
    {
        optional<string> unit;
    };

    struct GTypeInteger
    {
        // No elements
    };

    struct GTypeBoolean
    {
        // No elements
    };

    struct GTypeString
    {
        // No elements
    };

    struct GTypeEnumeration
    {
        optional<string> name; // Should not be optional but some tools don't include the enum correctly
    };

    struct GTypeBinary
    {
        optional<string> mime_type;
    };

    // Transformation structs
    struct LinearTransformation
    {
        optional<double> factor;
        optional<double> offset;
    };

}
