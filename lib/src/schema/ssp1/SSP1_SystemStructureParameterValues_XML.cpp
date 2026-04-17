

// This is a generated file, do not alter
// it is based on ssp1_ssv.toml

#include "SSP1_SystemStructureParameterValues_XML.hpp"
#include "SSP1_SystemStructureCommon_XML.hpp"

#include "xml_deserialize.hpp"

#include "ssp4cpp/utils/log.hpp"

namespace ssp4cpp::ssp1::ssv
{
    using namespace pugi;

    ssp4cpp::utils::log::Logger* log()
    {
        // Cache this logger locally so we avoid eager header initialization.
        static ssp4cpp::utils::log::Logger* logger =
            ssp4cpp::utils::log::make_logger("ssp4cpp.ssp1.ssv");
        return logger;
    }


    void from_xml(const xml_node &node, Real &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Real");

        utils::xml::get_attribute(node, obj.value  , "value"); // double
        utils::xml::get_optional_attribute(node, obj.unit   , "unit"); // string

        LOG_TRACE_L1(log(), "Completed Real");
    }


    void from_xml(const xml_node &node, Integer &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Integer");

        utils::xml::get_attribute(node, obj.value  , "value"); // int

        LOG_TRACE_L1(log(), "Completed Integer");
    }


    void from_xml(const xml_node &node, Boolean &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Boolean");

        utils::xml::get_attribute(node, obj.value  , "value"); // bool

        LOG_TRACE_L1(log(), "Completed Boolean");
    }


    void from_xml(const xml_node &node, String &obj)
    {
        LOG_TRACE_L1(log(), "Parsing String");

        utils::xml::get_attribute(node, obj.value  , "value"); // string

        LOG_TRACE_L1(log(), "Completed String");
    }


    void from_xml(const xml_node &node, Enumeration &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Enumeration");

        utils::xml::get_attribute(node, obj.value  , "value"); // string
        utils::xml::get_optional_attribute(node, obj.name   , "name"); // string

        LOG_TRACE_L1(log(), "Completed Enumeration");
    }


    void from_xml(const xml_node &node, Binary &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Binary");

        utils::xml::get_attribute(node, obj.value      , "value"); // string
        utils::xml::get_optional_attribute(node, obj.mime_type  , "mime-type"); // string

        LOG_TRACE_L1(log(), "Completed Binary");
    }


    void from_xml(const xml_node &node, TParameter &obj)
    {
        LOG_TRACE_L1(log(), "Parsing TParameter");

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

        LOG_TRACE_L1(log(), "Completed TParameter");
    }


    void from_xml(const xml_node &node, TParameters &obj)
    {
        LOG_TRACE_L1(log(), "Parsing TParameters");

        utils::xml::get_vector(node, obj.Parameters  , "ssv:Parameter"); // ssv::TParameter

        LOG_TRACE_L1(log(), "Completed TParameters");
    }


    void from_xml(const xml_node &node, ParameterSet &obj)
    {
        LOG_TRACE_L1(log(), "Parsing ParameterSet");

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

        LOG_TRACE_L1(log(), "Completed ParameterSet");
    }

}
