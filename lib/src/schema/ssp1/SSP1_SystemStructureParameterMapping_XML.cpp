

// This is a generated file, do not alter
// it is based on ssp1_ssm.toml

#include "SSP1_SystemStructureParameterMapping_XML.hpp"
#include "SSP1_SystemStructureCommon_XML.hpp"

#include "xml_deserialize.hpp"

#include "cutecpp/log.hpp"

namespace ssp4cpp::ssp1::ssm
{
    using namespace pugi;

    auto log = Logger("ssp4cpp.ssp1.ssm", LogLevel::info);


    void from_xml(const xml_node &node, TMappingEntry &obj)
    {
        log(ext_trace)("Parsing TMappingEntry");

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

        log(ext_trace)("Completed TMappingEntry");
    }


    void from_xml(const xml_node &node, ParameterMapping &obj)
    {
        log(ext_trace)("Parsing ParameterMapping");

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

        log(ext_trace)("Completed ParameterMapping");
    }

}
