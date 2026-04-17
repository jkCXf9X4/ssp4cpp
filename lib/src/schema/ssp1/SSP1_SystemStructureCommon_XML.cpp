

// This is a generated file, do not alter
// it is based on ssp1_ssc.toml

#include "SSP1_SystemStructureCommon_XML.hpp"


#include "xml_deserialize.hpp"

#include "ssp4cpp/utils/log.hpp"

namespace ssp4cpp::ssp1::ssc
{
    using namespace pugi;

    ssp4cpp::utils::log::Logger* log()
    {
        // Cache this logger locally so we avoid eager header initialization.
        static ssp4cpp::utils::log::Logger* logger =
            ssp4cpp::utils::log::make_logger("ssp4cpp.ssp1.ssc");
        return logger;
    }


    void from_xml(const xml_node &node, Annotation &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Annotation");

        utils::xml::get_attribute(node, obj.type  , "type"); // string
        utils::xml::get_optional_attribute(node, obj.any   , "any"); // string

        LOG_TRACE_L1(log(), "Completed Annotation");
    }


    void from_xml(const xml_node &node, TAnnotations &obj)
    {
        LOG_TRACE_L1(log(), "Parsing TAnnotations");

        utils::xml::get_vector(node, obj.Annotations  , "Annotation"); // Annotation

        LOG_TRACE_L1(log(), "Completed TAnnotations");
    }


    void from_xml(const xml_node &node, LinearTransformation &obj)
    {
        LOG_TRACE_L1(log(), "Parsing LinearTransformation");

        utils::xml::get_optional_attribute(node, obj.factor  , "factor"); // double
        utils::xml::get_optional_attribute(node, obj.offset  , "offset"); // double

        LOG_TRACE_L1(log(), "Completed LinearTransformation");
    }


    void from_xml(const xml_node &node, BooleanMapEntry &obj)
    {
        LOG_TRACE_L1(log(), "Parsing BooleanMapEntry");

        utils::xml::get_attribute(node, obj.source  , "source"); // bool
        utils::xml::get_attribute(node, obj.target  , "target"); // bool

        LOG_TRACE_L1(log(), "Completed BooleanMapEntry");
    }


    void from_xml(const xml_node &node, BooleanMappingTransformation &obj)
    {
        LOG_TRACE_L1(log(), "Parsing BooleanMappingTransformation");

        utils::xml::get_vector(node, obj.MapEntrys  , "ssc:MapEntry"); // ssc::BooleanMapEntry

        LOG_TRACE_L1(log(), "Completed BooleanMappingTransformation");
    }


    void from_xml(const xml_node &node, IntegerMapEntry &obj)
    {
        LOG_TRACE_L1(log(), "Parsing IntegerMapEntry");

        utils::xml::get_attribute(node, obj.source  , "source"); // int
        utils::xml::get_attribute(node, obj.target  , "target"); // int

        LOG_TRACE_L1(log(), "Completed IntegerMapEntry");
    }


    void from_xml(const xml_node &node, IntegerMappingTransformation &obj)
    {
        LOG_TRACE_L1(log(), "Parsing IntegerMappingTransformation");

        utils::xml::get_vector(node, obj.MapEntrys  , "ssc:MapEntry"); // ssc::IntegerMapEntry

        LOG_TRACE_L1(log(), "Completed IntegerMappingTransformation");
    }


    void from_xml(const xml_node &node, EnumerationMapEntry &obj)
    {
        LOG_TRACE_L1(log(), "Parsing EnumerationMapEntry");

        utils::xml::get_attribute(node, obj.source  , "source"); // string
        utils::xml::get_attribute(node, obj.target  , "target"); // string

        LOG_TRACE_L1(log(), "Completed EnumerationMapEntry");
    }


    void from_xml(const xml_node &node, EnumerationMappingTransformation &obj)
    {
        LOG_TRACE_L1(log(), "Parsing EnumerationMappingTransformation");

        utils::xml::get_vector(node, obj.MapEntrys  , "ssc:MapEntry"); // ssc::EnumerationMapEntry

        LOG_TRACE_L1(log(), "Completed EnumerationMappingTransformation");
    }


    void from_xml(const xml_node &node, Item &obj)
    {
        LOG_TRACE_L1(log(), "Parsing Item");

        utils::xml::get_attribute(node, obj.name   , "name"); // string
        utils::xml::get_attribute(node, obj.value  , "value"); // int

        LOG_TRACE_L1(log(), "Completed Item");
    }


    void from_xml(const xml_node &node, TEnumeration &obj)
    {
        LOG_TRACE_L1(log(), "Parsing TEnumeration");

        utils::xml::get_optional_attribute(node, obj.id           , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description  , "description"); // string
        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_vector(node, obj.Item         , "ssc:Item"); // ssc::Item
        utils::xml::get_optional_class(node, obj.Annotations  , "ssc:Annotations"); // ssc::TAnnotations

        LOG_TRACE_L1(log(), "Completed TEnumeration");
    }


    void from_xml(const xml_node &node, TEnumerations &obj)
    {
        LOG_TRACE_L1(log(), "Parsing TEnumerations");

        utils::xml::get_vector(node, obj.Enumerations  , "ssc:TEnumeration"); // ssc::TEnumeration

        LOG_TRACE_L1(log(), "Completed TEnumerations");
    }


    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        LOG_TRACE_L1(log(), "Parsing BaseUnit");

        utils::xml::get_optional_attribute(node, obj.kg      , "kg"); // double
        utils::xml::get_optional_attribute(node, obj.m       , "m"); // double
        utils::xml::get_optional_attribute(node, obj.s       , "s"); // double
        utils::xml::get_optional_attribute(node, obj.a       , "a"); // double
        utils::xml::get_optional_attribute(node, obj.k       , "k"); // double
        utils::xml::get_optional_attribute(node, obj.mol     , "mol"); // double
        utils::xml::get_optional_attribute(node, obj.cd      , "cd"); // double
        utils::xml::get_optional_attribute(node, obj.rad     , "rad"); // double
        utils::xml::get_optional_attribute(node, obj.factor  , "factor"); // double
        utils::xml::get_optional_attribute(node, obj.offset  , "offset"); // double

        LOG_TRACE_L1(log(), "Completed BaseUnit");
    }


    void from_xml(const xml_node &node, TUnit &obj)
    {
        LOG_TRACE_L1(log(), "Parsing TUnit");

        utils::xml::get_optional_attribute(node, obj.id           , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description  , "description"); // string
        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_class(node, obj.BaseUnit     , "BaseUnit"); // ssc::BaseUnit
        utils::xml::get_optional_class(node, obj.Annotations  , "ssc:Annotations"); // ssc::TAnnotations

        LOG_TRACE_L1(log(), "Completed TUnit");
    }


    void from_xml(const xml_node &node, TUnits &obj)
    {
        LOG_TRACE_L1(log(), "Parsing TUnits");

        utils::xml::get_vector(node, obj.Units  , "Unit"); // ssc::TUnit

        LOG_TRACE_L1(log(), "Completed TUnits");
    }


    void from_xml(const xml_node &node, GTypeReal &obj)
    {
        LOG_TRACE_L1(log(), "Parsing GTypeReal");

        utils::xml::get_optional_attribute(node, obj.unit  , "unit"); // string

        LOG_TRACE_L1(log(), "Completed GTypeReal");
    }


    void from_xml(const xml_node &node, GTypeInteger &obj)
    {
        LOG_TRACE_L1(log(), "Parsing GTypeInteger");



        LOG_TRACE_L1(log(), "Completed GTypeInteger");
    }


    void from_xml(const xml_node &node, GTypeBoolean &obj)
    {
        LOG_TRACE_L1(log(), "Parsing GTypeBoolean");



        LOG_TRACE_L1(log(), "Completed GTypeBoolean");
    }


    void from_xml(const xml_node &node, GTypeString &obj)
    {
        LOG_TRACE_L1(log(), "Parsing GTypeString");



        LOG_TRACE_L1(log(), "Completed GTypeString");
    }


    void from_xml(const xml_node &node, GTypeEnumeration &obj)
    {
        LOG_TRACE_L1(log(), "Parsing GTypeEnumeration");

        utils::xml::get_optional_attribute(node, obj.name  , "name"); // string

        LOG_TRACE_L1(log(), "Completed GTypeEnumeration");
    }


    void from_xml(const xml_node &node, GTypeBinary &obj)
    {
        LOG_TRACE_L1(log(), "Parsing GTypeBinary");

        utils::xml::get_optional_attribute(node, obj.mime_type  , "mime-type"); // string

        LOG_TRACE_L1(log(), "Completed GTypeBinary");
    }

}
