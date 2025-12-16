

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

        utils::xml::get_attribute(node, obj.value  , "value"); // double
        utils::xml::get_optional_attribute(node, obj.unit   , "unit"); // string

        log(ext_trace)("Completed Real");
    }


    void from_xml(const xml_node &node, Integer &obj)
    {
        log(ext_trace)("Parsing Integer");

        utils::xml::get_attribute(node, obj.value  , "value"); // int

        log(ext_trace)("Completed Integer");
    }


    void from_xml(const xml_node &node, Boolean &obj)
    {
        log(ext_trace)("Parsing Boolean");

        utils::xml::get_attribute(node, obj.value  , "value"); // bool

        log(ext_trace)("Completed Boolean");
    }


    void from_xml(const xml_node &node, String &obj)
    {
        log(ext_trace)("Parsing String");

        utils::xml::get_attribute(node, obj.value  , "value"); // string

        log(ext_trace)("Completed String");
    }


    void from_xml(const xml_node &node, Enumeration &obj)
    {
        log(ext_trace)("Parsing Enumeration");

        utils::xml::get_attribute(node, obj.value  , "value"); // string
        utils::xml::get_optional_attribute(node, obj.name   , "name"); // string

        log(ext_trace)("Completed Enumeration");
    }


    void from_xml(const xml_node &node, Binary &obj)
    {
        log(ext_trace)("Parsing Binary");

        utils::xml::get_attribute(node, obj.value      , "value"); // string
        utils::xml::get_optional_attribute(node, obj.mime_type  , "mime-type"); // string

        log(ext_trace)("Completed Binary");
    }


    void from_xml(const xml_node &node, TParameter &obj)
    {
        log(ext_trace)("Parsing TParameter");

        utils::xml::get_optional_attribute(node, obj.id           , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description  , "description"); // string
        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_optional_class(node, obj.Real         , "ssv:Real"); // ssv::Real
        utils::xml::get_optional_class(node, obj.Integer      , "ssv:Integer"); // ssv::Integer
        utils::xml::get_optional_class(node, obj.Boolean      , "ssv:Boolean"); // ssv::Boolean
        utils::xml::get_optional_class(node, obj.String       , "ssv:String"); // ssv::String
        utils::xml::get_optional_class(node, obj.Enumeration  , "ssv:Enumeration"); // ssv::Enumeration
        utils::xml::get_optional_class(node, obj.Binary       , "ssv:Binary"); // ssv::Binary
        utils::xml::get_optional_class(node, obj.Annotations  , "ssc:Annotations"); // ssc::TAnnotations

        log(ext_trace)("Completed TParameter");
    }


    void from_xml(const xml_node &node, TParameters &obj)
    {
        log(ext_trace)("Parsing TParameters");

        utils::xml::get_vector(node, obj.Parameters  , "ssv:Parameter"); // ssv::TParameter

        log(ext_trace)("Completed TParameters");
    }


    void from_xml(const xml_node &node, ParameterSet &obj)
    {
        log(ext_trace)("Parsing ParameterSet");

        utils::xml::get_optional_attribute(node, obj.version                , "version"); // string
        utils::xml::get_attribute(node, obj.name                   , "name"); // string
        utils::xml::get_optional_attribute(node, obj.id                     , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description            , "description"); // string
        utils::xml::get_optional_attribute(node, obj.author                 , "author"); // string
        utils::xml::get_optional_attribute(node, obj.fileversion            , "fileversion"); // string
        utils::xml::get_optional_attribute(node, obj.copyright              , "copyright"); // string
        utils::xml::get_optional_attribute(node, obj.license                , "license"); // string
        utils::xml::get_optional_attribute(node, obj.generationTool         , "generationTool"); // string
        utils::xml::get_optional_attribute(node, obj.generationDateAndTime  , "generationDateAndTime"); // string
        utils::xml::get_class(node, obj.Parameters             , "ssv:Parameters"); // ssv::TParameters
        utils::xml::get_optional_class(node, obj.Enumerations           , "ssc:Enumerations"); // ssc::TEnumerations
        utils::xml::get_optional_class(node, obj.Units                  , "Units"); // ssc::TUnits
        utils::xml::get_optional_class(node, obj.Annotations            , "ssc:Annotations"); // ssc::TAnnotations

        log(ext_trace)("Completed ParameterSet");
    }

}
