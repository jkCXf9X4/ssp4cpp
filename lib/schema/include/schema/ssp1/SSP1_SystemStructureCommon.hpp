

// This is a generated file, do not alter
// it is based on ssp1_ssc.toml
#pragma once

#include "common_interface.hpp"
#include "common_xml.hpp"

#include "SSP1_Enums.hpp"


#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::ssp1::ssc
{
    using namespace ssp4cpp::common::interfaces;
    using namespace ssp4cpp::common::xml;
    using namespace std;




    class Annotation : public IXmlNode
    {
    public:
        string type;
        optional<string> any;

        std::string to_string(void) const;
    };

    class TAnnotations : public IXmlNode
    {
    public:
        vector<Annotation> Annotations;

        std::string to_string(void) const;
    };

    class LinearTransformation : public IXmlNode
    {
    public:
        optional<double> factor;
        optional<double> offset;

        std::string to_string(void) const;
    };

    class BooleanMapEntry : public IXmlNode
    {
    public:
        bool source;
        bool target;

        std::string to_string(void) const;
    };

    class BooleanMappingTransformation : public IXmlNode
    {
    public:
        vector<ssc::BooleanMapEntry> MapEntrys;

        std::string to_string(void) const;
    };

    class IntegerMapEntry : public IXmlNode
    {
    public:
        int source;
        int target;

        std::string to_string(void) const;
    };

    class IntegerMappingTransformation : public IXmlNode
    {
    public:
        vector<ssc::IntegerMapEntry> MapEntrys;

        std::string to_string(void) const;
    };

    class EnumerationMapEntry : public IXmlNode
    {
    public:
        string source;
        string target;

        std::string to_string(void) const;
    };

    class EnumerationMappingTransformation : public IXmlNode
    {
    public:
        vector<ssc::EnumerationMapEntry> MapEntrys;

        std::string to_string(void) const;
    };

    class Item : public IXmlNode
    {
    public:
        string name;
        int value;

        std::string to_string(void) const;
    };

    class TEnumeration : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        string name;
        vector<ssc::Item> Item;
        optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
    };

    class TEnumerations : public IXmlNode
    {
    public:
        vector<ssc::TEnumeration> Enumerations;

        std::string to_string(void) const;
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

        std::string to_string(void) const;
    };

    class TUnit : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        string name;
        ssc::BaseUnit BaseUnit;
        optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
    };

    class TUnits : public IXmlNode
    {
    public:
        vector<ssc::TUnit> Units;

        std::string to_string(void) const;
    };

    class GTypeReal : public IXmlNode
    {
    public:
        optional<string> unit;

        std::string to_string(void) const;
    };

    class GTypeInteger : public IXmlNode
    {
    public:


        std::string to_string(void) const;
    };

    class GTypeBoolean : public IXmlNode
    {
    public:


        std::string to_string(void) const;
    };

    class GTypeString : public IXmlNode
    {
    public:


        std::string to_string(void) const;
    };

    class GTypeEnumeration : public IXmlNode
    {
    public:
        optional<string> name;

        std::string to_string(void) const;
    };

    class GTypeBinary : public IXmlNode
    {
    public:
        optional<string> mime_type;

        std::string to_string(void) const;
    };

}
