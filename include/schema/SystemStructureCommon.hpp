#pragma once

#include <string>
#include <vector>
#include <optional>

namespace ssc
{
    // Forward declarations
    // Annotation struct
    struct Annotation
    {
        std::optional<std::string> annotation_type;
        std::optional<std::string> any;
    };

    // Annotations struct
    struct TAnnotations
    {
        std::vector<Annotation> list;
    };

    struct BooleanMapEntry
    {
        bool source;
        bool target;
    };

    struct BooleanMappingTransformation
    {
        std::vector<BooleanMapEntry> list;
    };

    struct IntegerMapEntry
    {
        int source;
        int target;
    };

    struct IntegerMappingTransformation
    {
        std::vector<IntegerMapEntry> list;
    };

    struct EnumerationMapEntry
    {
        std::string source;
        std::string target;
    };

    struct EnumerationMappingTransformation
    {
        std::vector<EnumerationMapEntry> list;
    };

    // Struct definitions

    struct TEnumerations
    {
    };

    // Base unit struct
    struct BaseUnit
    {
        std::optional<int> kg;
        std::optional<int> m;
        std::optional<int> s;
        std::optional<int> a;
        std::optional<int> k;
        std::optional<int> mol;
        std::optional<int> cd;
        std::optional<int> rad;
        std::optional<double> factor;
        std::optional<double> offset;
    };

    // Units struct
    struct TUnits
    {
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::string name;
        BaseUnit baseUnit;
        std::optional<TAnnotations> annotations;
    };

    // GType structs
    struct GTypeReal
    {
        std::optional<std::string> unit;
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
        std::optional<std::string> name; // Should not be optional but some tools don't include the enum correctly
    };

    struct GTypeBinary
    {
        std::optional<std::string> mime_type;
    };

    // Transformation structs
    struct LinearTransformation
    {
        std::optional<double> factor;
        std::optional<double> offset;
    };

}