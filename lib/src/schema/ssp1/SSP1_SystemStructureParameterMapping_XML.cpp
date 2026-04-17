

// This is a generated file, do not alter
// it is based on ssp1_ssm.toml

#include "SSP1_SystemStructureParameterMapping_XML.hpp"
#include "SSP1_SystemStructureCommon_XML.hpp"

#include "xml_deserialize.hpp"

#include "ssp4cpp/utils/log.hpp"

namespace ssp4cpp::ssp1::ssm
{
    using namespace pugi;

    ssp4cpp::utils::log::Logger* log()
    {
        // Cache this logger locally so we avoid eager header initialization.
        static ssp4cpp::utils::log::Logger* logger =
            ssp4cpp::utils::log::make_logger("ssp4cpp.ssp1.ssm", quill::LogLevel::TraceL1);
        return logger;
    }


    void from_xml(const xml_node &node, TMappingEntry &obj)
    {
        LOG_TRACE_L1(log(), "Parsing TMappingEntry");

        utils::xml::get_optional_attribute(node, obj.id                                , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description                       , "description"); // string
        utils::xml::get_attribute(node, obj.source                            , "source"); // string
        utils::xml::get_attribute(node, obj.target                            , "target"); // string
        utils::xml::get_optional_attribute(node, obj.suppressUnitConversion            , "suppressUnitConversion"); // bool
        utils::xml::get_optional_class(node, obj.LinearTransformation              , "ssc:LinearTransformation"); // ssc::LinearTransformation
        utils::xml::get_optional_class(node, obj.BooleanMappingTransformation      , "ssc:BooleanMappingTransformation"); // ssc::BooleanMappingTransformation
        utils::xml::get_optional_class(node, obj.IntegerMappingTransformation      , "ssc:IntegerMappingTransformation"); // ssc::IntegerMappingTransformation
        utils::xml::get_optional_class(node, obj.EnumerationMappingTransformation  , "ssc:EnumerationMappingTransformation"); // ssc::EnumerationMappingTransformation
        utils::xml::get_optional_class(node, obj.Annotations                       , "ssc:Annotations"); // ssc::TAnnotations

        LOG_TRACE_L1(log(), "Completed TMappingEntry");
    }


    void from_xml(const xml_node &node, ParameterMapping &obj)
    {
        LOG_TRACE_L1(log(), "Parsing ParameterMapping");

        utils::xml::get_attribute(node, obj.version                , "version"); // string
        utils::xml::get_optional_attribute(node, obj.id                     , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description            , "description"); // string
        utils::xml::get_optional_attribute(node, obj.author                 , "author"); // string
        utils::xml::get_optional_attribute(node, obj.fileversion            , "fileversion"); // string
        utils::xml::get_optional_attribute(node, obj.copyright              , "copyright"); // string
        utils::xml::get_optional_attribute(node, obj.license                , "license"); // string
        utils::xml::get_optional_attribute(node, obj.generationTool         , "generationTool"); // string
        utils::xml::get_optional_attribute(node, obj.generationDateAndTime  , "generationDateAndTime"); // string
        utils::xml::get_vector(node, obj.MappingEntry           , "ssm:MappingEntry"); // ssm::TMappingEntry
        utils::xml::get_optional_class(node, obj.Annotations            , "ssc:Annotations"); // ssc::TAnnotations

        LOG_TRACE_L1(log(), "Completed ParameterMapping");
    }

}
