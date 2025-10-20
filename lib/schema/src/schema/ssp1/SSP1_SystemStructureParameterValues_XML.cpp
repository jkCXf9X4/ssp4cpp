

// This is a generated file, do not alter
// it is based on ssp1_ssv.toml

#include "SSP1_SystemStructureParameterValues_XML.hpp"
#include "SSP1_SystemStructureCommon_XML.hpp"

#include "xml_deserialize.hpp"

#include "utils/log.hpp"

namespace ssp4cpp::ssp1::ssv
{
    using namespace pugi;
    using namespace common;

    auto log = Logger("ssp4cpp.ssp1.ssv", LogLevel::info);


    void from_xml(const xml_node &node, Real &obj)
    {
        log.ext_trace("Parsing Real");
        
        ssp4cpp::common::xml::parse_xml(node, obj.value  , "value");
        ssp4cpp::common::xml::parse_xml(node, obj.unit   , "unit");

        log.ext_trace("Completed Real");
    }


    void from_xml(const xml_node &node, Integer &obj)
    {
        log.ext_trace("Parsing Integer");
        
        ssp4cpp::common::xml::parse_xml(node, obj.value  , "value");

        log.ext_trace("Completed Integer");
    }


    void from_xml(const xml_node &node, Boolean &obj)
    {
        log.ext_trace("Parsing Boolean");
        
        ssp4cpp::common::xml::parse_xml(node, obj.value  , "value");

        log.ext_trace("Completed Boolean");
    }


    void from_xml(const xml_node &node, String &obj)
    {
        log.ext_trace("Parsing String");
        
        ssp4cpp::common::xml::parse_xml(node, obj.value  , "value");

        log.ext_trace("Completed String");
    }


    void from_xml(const xml_node &node, Enumeration &obj)
    {
        log.ext_trace("Parsing Enumeration");
        
        ssp4cpp::common::xml::parse_xml(node, obj.value  , "value");
        ssp4cpp::common::xml::parse_xml(node, obj.name   , "name");

        log.ext_trace("Completed Enumeration");
    }


    void from_xml(const xml_node &node, Binary &obj)
    {
        log.ext_trace("Parsing Binary");
        
        ssp4cpp::common::xml::parse_xml(node, obj.value      , "value");
        ssp4cpp::common::xml::parse_xml(node, obj.mime_type  , "mime-type");

        log.ext_trace("Completed Binary");
    }


    void from_xml(const xml_node &node, TParameter &obj)
    {
        log.ext_trace("Parsing TParameter");
        
        ssp4cpp::common::xml::parse_xml(node, obj.id           , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description  , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.Real         , "ssv:Real");
        ssp4cpp::common::xml::parse_xml(node, obj.Integer      , "ssv:Integer");
        ssp4cpp::common::xml::parse_xml(node, obj.Boolean      , "ssv:Boolean");
        ssp4cpp::common::xml::parse_xml(node, obj.String       , "ssv:String");
        ssp4cpp::common::xml::parse_xml(node, obj.Enumeration  , "ssv:Enumeration");
        ssp4cpp::common::xml::parse_xml(node, obj.Binary       , "ssv:Binary");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        log.ext_trace("Completed TParameter");
    }


    void from_xml(const xml_node &node, TParameters &obj)
    {
        log.ext_trace("Parsing TParameters");
        
        ssp4cpp::common::xml::parse_xml(node, obj.Parameters  , "ssv:Parameter");

        log.ext_trace("Completed TParameters");
    }


    void from_xml(const xml_node &node, ParameterSet &obj)
    {
        log.ext_trace("Parsing ParameterSet");
        
        ssp4cpp::common::xml::parse_xml(node, obj.version                , "version");
        ssp4cpp::common::xml::parse_xml(node, obj.name                   , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.id                     , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description            , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.author                 , "author");
        ssp4cpp::common::xml::parse_xml(node, obj.fileversion            , "fileversion");
        ssp4cpp::common::xml::parse_xml(node, obj.copyright              , "copyright");
        ssp4cpp::common::xml::parse_xml(node, obj.license                , "license");
        ssp4cpp::common::xml::parse_xml(node, obj.generationTool         , "generationTool");
        ssp4cpp::common::xml::parse_xml(node, obj.generationDateAndTime  , "generationDateAndTime");
        ssp4cpp::common::xml::parse_xml(node, obj.Parameters             , "ssv:Parameters");
        ssp4cpp::common::xml::parse_xml(node, obj.Enumerations           , "ssc:Enumerations");
        ssp4cpp::common::xml::parse_xml(node, obj.Units                  , "Units");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations            , "ssc:Annotations");

        log.ext_trace("Completed ParameterSet");
    }

}
