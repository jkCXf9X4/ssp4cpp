#pragma once

#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::ssp1::ssc
{
    using namespace std;

    // Annotation struct
    typedef struct
    {
        optional<string> annotation_type;
        optional<string> any;
    } Annotation;

    // Annotations struct
    typedef struct
    {
        vector<Annotation> list;
    } TAnnotations;

    typedef struct
    {
        bool source;
        bool target;
    } BooleanMapEntry;

    typedef struct
    {
        vector<BooleanMapEntry> list;
    } BooleanMappingTransformation;

    typedef struct
    {
        int source;
        int target;
    } IntegerMapEntry;

    typedef struct
    {
        vector<IntegerMapEntry> list;
    } IntegerMappingTransformation;

    typedef struct
    {
        string source;
        string target;
    } EnumerationMapEntry;

    typedef struct
    {
        vector<EnumerationMapEntry> list;
    } EnumerationMappingTransformation;

    // Struct definitions

    typedef struct
    {
    } TEnumerations;

    // Base unit struct
    typedef struct
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
    } BaseUnit;

    // Units struct
    typedef struct
    {
        optional<string> id;
        optional<string> description;
        string name;
        BaseUnit baseUnit;
        optional<TAnnotations> annotations;
    } TUnits;

    // GType structs
    typedef struct
    {
        optional<string> unit;
    } GTypeReal;

    typedef struct
    {
        // No elements
    } GTypeInteger;

    typedef struct
    {
        // No elements
    } GTypeBoolean;

    typedef struct
    {
        // No elements
    } GTypeString;

    typedef struct
    {
        optional<string> name; // Should not be optional but some tools don't include the enum correctly
    } GTypeEnumeration;

    typedef struct
    {
        optional<string> mime_type;
    } GTypeBinary;

    // Transformation structs
    typedef struct
    {
        optional<double> factor;
        optional<double> offset;
    } LinearTransformation;

}
