

// This is a generated file, do not alter
// it is based on ssp1_ssv.toml

#include "SSP1_SystemStructureParameterValues_XML.hpp"
#include "SSP1_SystemStructureCommon_XML.hpp"

#include "xml_deserialize.hpp"

#include "cutecpp/log.hpp"

namespace ssp4cpp::ssp1::ssv
{
    using namespace pugi;

    auto log = Logger("ssp4cpp.ssp1.ssv", LogLevel::info);


    void from_xml(const xml_node &node, Real &obj)
    {
        log(ext_trace)("Parsing Real");
        

        utils::xml::parse_xml(node, obj.value  , "value");
        utils::xml::parse_xml(node, obj.unit   , "unit");

        log(ext_trace)("Completed Real");
    }


    void from_xml(const xml_node &node, Integer &obj)
    {
        log(ext_trace)("Parsing Integer");
        

        utils::xml::parse_xml(node, obj.value  , "value");

        log(ext_trace)("Completed Integer");
    }


    void from_xml(const xml_node &node, Boolean &obj)
    {
        log(ext_trace)("Parsing Boolean");
        

        utils::xml::parse_xml(node, obj.value  , "value");

        log(ext_trace)("Completed Boolean");
    }


    void from_xml(const xml_node &node, String &obj)
    {
        log(ext_trace)("Parsing String");
        

        utils::xml::parse_xml(node, obj.value  , "value");

        log(ext_trace)("Completed String");
    }


    void from_xml(const xml_node &node, Enumeration &obj)
    {
        log(ext_trace)("Parsing Enumeration");
        

        utils::xml::parse_xml(node, obj.value  , "value");
        utils::xml::parse_xml(node, obj.name   , "name");

        log(ext_trace)("Completed Enumeration");
    }


    void from_xml(const xml_node &node, Binary &obj)
    {
        log(ext_trace)("Parsing Binary");
        

        utils::xml::parse_xml(node, obj.value      , "value");
        utils::xml::parse_xml(node, obj.mime_type  , "mime-type");

        log(ext_trace)("Completed Binary");
    }


    void from_xml(const xml_node &node, TParameter &obj)
    {
        log(ext_trace)("Parsing TParameter");
        

        utils::xml::parse_xml(node, obj.id           , "id");
        utils::xml::parse_xml(node, obj.description  , "description");
        utils::xml::parse_xml(node, obj.name         , "name");
        utils::xml::parse_xml(node, obj.Real         , "ssv:Real");
        utils::xml::parse_xml(node, obj.Integer      , "ssv:Integer");
        utils::xml::parse_xml(node, obj.Boolean      , "ssv:Boolean");
        utils::xml::parse_xml(node, obj.String       , "ssv:String");
        utils::xml::parse_xml(node, obj.Enumeration  , "ssv:Enumeration");
        utils::xml::parse_xml(node, obj.Binary       , "ssv:Binary");
        utils::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        log(ext_trace)("Completed TParameter");
    }


    void from_xml(const xml_node &node, TParameters &obj)
    {
        log(ext_trace)("Parsing TParameters");
        

        utils::xml::parse_xml(node, obj.Parameters  , "ssv:Parameter");

        log(ext_trace)("Completed TParameters");
    }


    void from_xml(const xml_node &node, ParameterSet &obj)
    {
        log(ext_trace)("Parsing ParameterSet");
        

        utils::xml::parse_xml(node, obj.version                , "version");
        utils::xml::parse_xml(node, obj.name                   , "name");
        utils::xml::parse_xml(node, obj.id                     , "id");
        utils::xml::parse_xml(node, obj.description            , "description");
        utils::xml::parse_xml(node, obj.author                 , "author");
        utils::xml::parse_xml(node, obj.fileversion            , "fileversion");
        utils::xml::parse_xml(node, obj.copyright              , "copyright");
        utils::xml::parse_xml(node, obj.license                , "license");
        utils::xml::parse_xml(node, obj.generationTool         , "generationTool");
        utils::xml::parse_xml(node, obj.generationDateAndTime  , "generationDateAndTime");
        utils::xml::parse_xml(node, obj.Parameters             , "ssv:Parameters");
        utils::xml::parse_xml(node, obj.Enumerations           , "ssc:Enumerations");
        utils::xml::parse_xml(node, obj.Units                  , "Units");
        utils::xml::parse_xml(node, obj.Annotations            , "ssc:Annotations");

        log(ext_trace)("Completed ParameterSet");
    }

}
