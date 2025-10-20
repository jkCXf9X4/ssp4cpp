

// This is a generated file, do not alter
// it is based on ssp1_ssm.toml

#include "SSP1_SystemStructureParameterMapping_XML.hpp"
#include "SSP1_SystemStructureCommon_XML.hpp"

#include "xml_deserialize.hpp"

#include "utils/log.hpp"

namespace ssp4cpp::ssp1::ssm
{
    using namespace pugi;

    auto log = Logger("ssp4cpp.ssp1.ssm", LogLevel::info);


    void from_xml(const xml_node &node, TMappingEntry &obj)
    {
        log(ext_trace)("Parsing TMappingEntry");
        

        utils::xml::parse_xml(node, obj.id                                , "id");
        utils::xml::parse_xml(node, obj.description                       , "description");
        utils::xml::parse_xml(node, obj.source                            , "source");
        utils::xml::parse_xml(node, obj.target                            , "target");
        utils::xml::parse_xml(node, obj.suppressUnitConversion            , "suppressUnitConversion");
        utils::xml::parse_xml(node, obj.LinearTransformation              , "ssc:LinearTransformation");
        utils::xml::parse_xml(node, obj.BooleanMappingTransformation      , "ssc:BooleanMappingTransformation");
        utils::xml::parse_xml(node, obj.IntegerMappingTransformation      , "ssc:IntegerMappingTransformation");
        utils::xml::parse_xml(node, obj.EnumerationMappingTransformation  , "ssc:EnumerationMappingTransformation");
        utils::xml::parse_xml(node, obj.Annotations                       , "ssc:Annotations");

        log(ext_trace)("Completed TMappingEntry");
    }


    void from_xml(const xml_node &node, ParameterMapping &obj)
    {
        log(ext_trace)("Parsing ParameterMapping");
        

        utils::xml::parse_xml(node, obj.version                , "version");
        utils::xml::parse_xml(node, obj.id                     , "id");
        utils::xml::parse_xml(node, obj.description            , "description");
        utils::xml::parse_xml(node, obj.author                 , "author");
        utils::xml::parse_xml(node, obj.fileversion            , "fileversion");
        utils::xml::parse_xml(node, obj.copyright              , "copyright");
        utils::xml::parse_xml(node, obj.license                , "license");
        utils::xml::parse_xml(node, obj.generationTool         , "generationTool");
        utils::xml::parse_xml(node, obj.generationDateAndTime  , "generationDateAndTime");
        utils::xml::parse_xml(node, obj.MappingEntry           , "ssm:MappingEntry");
        utils::xml::parse_xml(node, obj.Annotations            , "ssc:Annotations");

        log(ext_trace)("Completed ParameterMapping");
    }

}
