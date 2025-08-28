

// This is a generated file, do not alter
// it is based on ssp1_ssm.toml
#pragma once

#include "common_interface.hpp"
#include "common_xml.hpp"


#include "SSP1_SystemStructureCommon.hpp"

#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::ssp1::ssm
{
    using namespace ssp4cpp::common::interfaces;
    using namespace ssp4cpp::common::xml;
    using namespace std;




    class TMappingEntry : public IXmlNode
    {
    public:
        optional<string> id;
        optional<string> description;
        string source;
        string target;
        optional<bool> suppressUnitConversion;
        optional<ssc::LinearTransformation> LinearTransformation;
        optional<ssc::BooleanMappingTransformation> BooleanMappingTransformation;
        optional<ssc::IntegerMappingTransformation> IntegerMappingTransformation;
        optional<ssc::EnumerationMappingTransformation> EnumerationMappingTransformation;
        optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
    };

    class ParameterMapping : public IXmlNode
    {
    public:
        string version;
        optional<string> id;
        optional<string> description;
        optional<string> author;
        optional<string> fileversion;
        optional<string> copyright;
        optional<string> license;
        optional<string> generationTool;
        optional<string> generationDateAndTime;
        vector<ssm::TMappingEntry> MappingEntry;
        optional<ssc::TAnnotations> Annotations;

        std::string to_string(void) const;
    };

}
