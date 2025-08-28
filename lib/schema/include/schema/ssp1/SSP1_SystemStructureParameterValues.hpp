

// This is a generated file, do not alter
// it is based on ssp1_ssv.toml
#pragma once

#include "common_interface.hpp"
#include "common_xml.hpp"


#include "SSP1_SystemStructureCommon.hpp"

#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::ssp1::ssv
{
    using namespace ssp4cpp::common::interfaces;
    using namespace ssp4cpp::common::xml;
    using namespace std;




    class Real : public IXmlNode
    {
    public:
        double value;
        optional<string> unit;

        std::string to_string(void) const;
    };

    class Integer : public IXmlNode
    {
    public:
        int value;

        std::string to_string(void) const;
    };

    class Boolean : public IXmlNode
    {
    public:
        bool value;

        std::string to_string(void) const;
    };

    class String : public IXmlNode
    {
    public:
        string value;

        std::string to_string(void) const;
    };

    class Enumeration : public IXmlNode
    {
    public:
        string value;
        optional<string> name;

        std::string to_string(void) const;
    };

    class Binary : public IXmlNode
    {
    public:
        string value;
        optional<string> mime_type;

        std::string to_string(void) const;
    };

    class TParameter : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        string name;
        optional<ssv::Real> Real;
        optional<ssv::Integer> Integer;
        optional<ssv::Boolean> Boolean;
        optional<ssv::String> String;
        optional<ssv::Enumeration> Enumeration;
        optional<ssv::Binary> Binary;
        optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
    };

    class TParameters : public IXmlNode
    {
    public:
        vector<ssv::TParameter> Parameters;

        std::string to_string(void) const;
    };

    class ParameterSet : public IXmlNode
    {
    public:
        string version;
        string name;
        optional<string> id;
        optional<string> description;
        optional<string> author;
        optional<string> fileversion;
        optional<string> copyright;
        optional<string> license;
        optional<string> generationTool;
        optional<string> generationDateAndTime;
        ssv::TParameters TParameters;
        optional<ssc::TEnumerations> Enumerations;
        optional<ssc::TUnits> Units;
        optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
    };

}
