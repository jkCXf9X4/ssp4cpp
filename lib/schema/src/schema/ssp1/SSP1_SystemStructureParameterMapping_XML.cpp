

// This is a generated file, do not alter
// it is based on ssp1_ssm.toml

#include "SSP1_SystemStructureParameterMapping_XML.hpp"
#include "SSP1_SystemStructureCommon_XML.hpp"

#include "xml_deserialize.hpp"

#include "common_log.hpp"

namespace ssp4cpp::ssp1::ssm
{
    using namespace pugi;
    using namespace common;

    auto log = Logger("ssp4cpp.ssp1.ssm", LogLevel::info);


    void from_xml(const xml_node &node, TMappingEntry &obj)
    {
        log.ext_trace("Parsing TMappingEntry");
        
        ssp4cpp::common::xml::parse_xml(node, obj.id                                , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description                       , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.source                            , "source");
        ssp4cpp::common::xml::parse_xml(node, obj.target                            , "target");
        ssp4cpp::common::xml::parse_xml(node, obj.suppressUnitConversion            , "suppressUnitConversion");
        ssp4cpp::common::xml::parse_xml(node, obj.LinearTransformation              , "ssc:LinearTransformation");
        ssp4cpp::common::xml::parse_xml(node, obj.BooleanMappingTransformation      , "ssc:BooleanMappingTransformation");
        ssp4cpp::common::xml::parse_xml(node, obj.IntegerMappingTransformation      , "ssc:IntegerMappingTransformation");
        ssp4cpp::common::xml::parse_xml(node, obj.EnumerationMappingTransformation  , "ssc:EnumerationMappingTransformation");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations                       , "ssc:Annotations");

        log.ext_trace("Completed TMappingEntry");
    }


    void from_xml(const xml_node &node, ParameterMapping &obj)
    {
        log.ext_trace("Parsing ParameterMapping");
        
        ssp4cpp::common::xml::parse_xml(node, obj.version                , "version");
        ssp4cpp::common::xml::parse_xml(node, obj.id                     , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description            , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.author                 , "author");
        ssp4cpp::common::xml::parse_xml(node, obj.fileversion            , "fileversion");
        ssp4cpp::common::xml::parse_xml(node, obj.copyright              , "copyright");
        ssp4cpp::common::xml::parse_xml(node, obj.license                , "license");
        ssp4cpp::common::xml::parse_xml(node, obj.generationTool         , "generationTool");
        ssp4cpp::common::xml::parse_xml(node, obj.generationDateAndTime  , "generationDateAndTime");
        ssp4cpp::common::xml::parse_xml(node, obj.MappingEntry           , "ssm:MappingEntry");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations            , "ssc:Annotations");

        log.ext_trace("Completed ParameterMapping");
    }

}
