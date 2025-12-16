

// This is a generated file, do not alter
// it is based on ssp1_ssc.toml
#pragma once

#include "ssp4cpp/utils/interface.hpp"

#include "ssp4cpp/schema/ssp1/SSP1_Enums.hpp"


#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::ssp1::ssc
{
    using namespace utils::interfaces;






    class Annotation : public IXmlNode
    {
    public:
        std::string type;
        std::optional<std::string> any;

        std::string to_string(void) const;
    };

    class TAnnotations : public IXmlNode
    {
    public:
        std::vector<Annotation> Annotations;

        std::string to_string(void) const;
    };

    class LinearTransformation : public IXmlNode
    {
    public:
        std::optional<double> factor;
        std::optional<double> offset;

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
        std::vector<ssc::BooleanMapEntry> MapEntrys;

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
        std::vector<ssc::IntegerMapEntry> MapEntrys;

        std::string to_string(void) const;
    };

    class EnumerationMapEntry : public IXmlNode
    {
    public:
        std::string source;
        std::string target;

        std::string to_string(void) const;
    };

    class EnumerationMappingTransformation : public IXmlNode
    {
    public:
        std::vector<ssc::EnumerationMapEntry> MapEntrys;

        std::string to_string(void) const;
    };

    class Item : public IXmlNode
    {
    public:
        std::string name;
        int value;

        std::string to_string(void) const;
    };

    class TEnumeration : public IXmlNode
    {
    public:
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::string name;
        std::vector<ssc::Item> Item;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
    };

    class TEnumerations : public IXmlNode
    {
    public:
        std::vector<ssc::TEnumeration> Enumerations;

        std::string to_string(void) const;
    };

    class BaseUnit : public IXmlNode
    {
    public:
        std::optional<double> kg;
        std::optional<double> m;
        std::optional<double> s;
        std::optional<double> a;
        std::optional<double> k;
        std::optional<double> mol;
        std::optional<double> cd;
        std::optional<double> rad;
        std::optional<double> factor;
        std::optional<double> offset;

        std::string to_string(void) const;
    };

    class TUnit : public IXmlNode
    {
    public:
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::string name;
        ssc::BaseUnit BaseUnit;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
    };

    class TUnits : public IXmlNode
    {
    public:
        std::vector<ssc::TUnit> Units;

        std::string to_string(void) const;
    };

    class GTypeReal : public IXmlNode
    {
    public:
        std::optional<std::string> unit;

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
        std::optional<std::string> name;

        std::string to_string(void) const;
    };

    class GTypeBinary : public IXmlNode
    {
    public:
        std::optional<std::string> mime_type;

        std::string to_string(void) const;
    };

}
