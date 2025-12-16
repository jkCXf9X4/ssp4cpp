

// This is a generated file, do not alter
// it is based on ssp1_ssm.toml
#pragma once

#include "ssp4cpp/utils/interface.hpp"


#include "ssp4cpp/schema/ssp1/SSP1_SystemStructureCommon.hpp"

#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::ssp1::ssm
{
    using namespace utils::interfaces;






    class TMappingEntry : public IXmlNode
    {
    public:
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::string source;
        std::string target;
        std::optional<bool> suppressUnitConversion;
        std::optional<ssc::LinearTransformation> LinearTransformation;
        std::optional<ssc::BooleanMappingTransformation> BooleanMappingTransformation;
        std::optional<ssc::IntegerMappingTransformation> IntegerMappingTransformation;
        std::optional<ssc::EnumerationMappingTransformation> EnumerationMappingTransformation;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
    };

    class ParameterMapping : public IXmlNode
    {
    public:
        std::string version;
        std::optional<std::string> id;
        std::optional<std::string> description;
        std::optional<std::string> author;
        std::optional<std::string> fileversion;
        std::optional<std::string> copyright;
        std::optional<std::string> license;
        std::optional<std::string> generationTool;
        std::optional<std::string> generationDateAndTime;
        std::vector<ssm::TMappingEntry> MappingEntry;
        std::optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
    };

}
