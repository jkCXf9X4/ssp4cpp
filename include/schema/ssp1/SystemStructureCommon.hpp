#pragma once

#include <string>
#include <vector>
#include <optional>
#include <iostream>

#include "IXmlNode.hpp"

#include "SSP_Enums.hpp"
using namespace ssp4cpp::interfaces;

namespace ssp4cpp::ssp1::ssc
{

    class Annotation : public IXmlNode
    {
    public:
        string type;
        optional<string> any;

        string to_string(void) const;
    };


    class TAnnotations : public IXmlNode
    {
    public:
        vector<Annotation> Annotations;

        string to_string(void) const;
    };


    class LinearTransformation : public IXmlNode
    {
    public:
        optional<double> factor;
        optional<double> offset;

        string to_string(void) const;
    };


    class BooleanMapEntry : public IXmlNode
    {
    public:
        bool source;
        bool target;

        string to_string(void) const;
    };


    class BooleanMappingTransformation : public IXmlNode
    {
    public:
        vector<ssc::BooleanMapEntry> MapEntrys;

        string to_string(void) const;
    };


    class IntegerMapEntry : public IXmlNode
    {
    public:
        int source;
        int target;

        string to_string(void) const;
    };


    class IntegerMappingTransformation : public IXmlNode
    {
    public:
        vector<ssc::IntegerMapEntry> MapEntrys;

        string to_string(void) const;
    };


    class EnumerationMapEntry : public IXmlNode
    {
    public:
        string source;
        string target;

        string to_string(void) const;
    };


    class EnumerationMappingTransformation : public IXmlNode
    {
    public:
        vector<ssc::EnumerationMapEntry> MapEntrys;

        string to_string(void) const;
    };


    class Item : public IXmlNode
    {
    public:
        string name;
        int value;

        string to_string(void) const;
    };


    class TEnumeration : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        string name;
        vector<ssc::Item> Item;
        optional<ssc::TAnnotations> Annotations;

        string to_string(void) const;
    };


    class TEnumerations : public IXmlNode
    {
    public:
        vector<ssc::TEnumeration> Enumerations;

        string to_string(void) const;
    };


    class BaseUnit : public IXmlNode
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

        string to_string(void) const;
    };


    class TUnit : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        string name;
        ssc::BaseUnit BaseUnit;
        optional<ssc::TAnnotations> Annotations;

        string to_string(void) const;
    };


    class TUnits : public IXmlNode
    {
    public:
        vector<ssc::TUnit> Units;

        string to_string(void) const;
    };


    class GTypeReal : public IXmlNode
    {
    public:
        optional<string> unit;

        string to_string(void) const;
    };


    class GTypeInteger : public IXmlNode
    {
    public:


        string to_string(void) const;
    };


    class GTypeBoolean : public IXmlNode
    {
    public:


        string to_string(void) const;
    };


    class GTypeString : public IXmlNode
    {
    public:


        string to_string(void) const;
    };


    class GTypeEnumeration : public IXmlNode
    {
    public:
        optional<string> name;

        string to_string(void) const;
    };


    class GTypeBinary : public IXmlNode
    {
    public:
        optional<string> mime_type;

        string to_string(void) const;
    };


}
