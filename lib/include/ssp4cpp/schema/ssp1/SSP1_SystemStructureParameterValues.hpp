

// This is a generated file, do not alter
// it is based on ssp1_ssv.toml
#pragma once

#include "ssp4cpp/utils/interface.hpp"


#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureCommon.hpp"

#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::ssp1::ssv
{
    using namespace utils::interfaces;






    class Real : public IXmlNode
    {
    public:
        double value;
        std::optional<std::string> unit;

        std::string to_string(void) const override;
    };

    class Integer : public IXmlNode
    {
    public:
        int value;

        std::string to_string(void) const override;
    };

    class Boolean : public IXmlNode
    {
    public:
        bool value;

        std::string to_string(void) const override;
    };

    class String : public IXmlNode
    {
    public:
        std::string value;

        std::string to_string(void) const override;
    };

    class Enumeration : public IXmlNode
    {
    public:
        std::string value;
        std::optional<std::string> name;

        std::string to_string(void) const override;
    };

    class Binary : public IXmlNode
    {
    public:
        std::string value;
        std::optional<std::string> mime_type;

        std::string to_string(void) const override;
    };

    class TParameter : public IXmlNode
    {
    public:
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::string name;
        std::optional<ssv::Real> Real;
        std::optional<ssv::Integer> Integer;
        std::optional<ssv::Boolean> Boolean;
        std::optional<ssv::String> String;
        std::optional<ssv::Enumeration> Enumeration;
        std::optional<ssv::Binary> Binary;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const override;
    };

    class TParameters : public IXmlNode
    {
    public:
        std::vector<ssv::TParameter> Parameters;

        std::string to_string(void) const override;
    };

    class ParameterSet : public IXmlNode
    {
    public:
        std::optional<std::string> version;
        std::string name;
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::optional<std::string> author;
        std::optional<std::string> fileversion;
        std::optional<std::string> copyright;
        std::optional<std::string> license;
        std::optional<std::string> generationTool;
        std::optional<std::string> generationDateAndTime;
        ssv::TParameters Parameters;
        std::optional<ssc::TEnumerations> Enumerations;
        std::optional<ssc::TUnits> Units;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const override;
    };

}
