

// This is a generated file, do not alter
// it is based on ssp1_ssc.toml

#include "SSP1_SystemStructureCommon_XML.hpp"


#include "xml_deserialize.hpp"

#include "cutecpp/log.hpp"

namespace ssp4cpp::ssp1::ssc
{
    using namespace pugi;

    auto log = Logger("ssp4cpp.ssp1.ssc", LogLevel::info);


    void from_xml(const xml_node &node, Annotation &obj)
    {
        log(ext_trace)("Parsing Annotation");

        utils::xml::get_attribute(node, obj.type  , "type"); // string
        utils::xml::get_optional_attribute(node, obj.any   , "any"); // string

        log(ext_trace)("Completed Annotation");
    }


    void from_xml(const xml_node &node, TAnnotations &obj)
    {
        log(ext_trace)("Parsing TAnnotations");

        utils::xml::get_vector(node, obj.Annotations  , "Annotation"); // Annotation

        log(ext_trace)("Completed TAnnotations");
    }


    void from_xml(const xml_node &node, LinearTransformation &obj)
    {
        log(ext_trace)("Parsing LinearTransformation");

        utils::xml::get_optional_attribute(node, obj.factor  , "factor"); // double
        utils::xml::get_optional_attribute(node, obj.offset  , "offset"); // double

        log(ext_trace)("Completed LinearTransformation");
    }


    void from_xml(const xml_node &node, BooleanMapEntry &obj)
    {
        log(ext_trace)("Parsing BooleanMapEntry");

        utils::xml::get_attribute(node, obj.source  , "source"); // bool
        utils::xml::get_attribute(node, obj.target  , "target"); // bool

        log(ext_trace)("Completed BooleanMapEntry");
    }


    void from_xml(const xml_node &node, BooleanMappingTransformation &obj)
    {
        log(ext_trace)("Parsing BooleanMappingTransformation");

        utils::xml::get_vector(node, obj.MapEntrys  , "ssc:MapEntry"); // ssc::BooleanMapEntry

        log(ext_trace)("Completed BooleanMappingTransformation");
    }


    void from_xml(const xml_node &node, IntegerMapEntry &obj)
    {
        log(ext_trace)("Parsing IntegerMapEntry");

        utils::xml::get_attribute(node, obj.source  , "source"); // int
        utils::xml::get_attribute(node, obj.target  , "target"); // int

        log(ext_trace)("Completed IntegerMapEntry");
    }


    void from_xml(const xml_node &node, IntegerMappingTransformation &obj)
    {
        log(ext_trace)("Parsing IntegerMappingTransformation");

        utils::xml::get_vector(node, obj.MapEntrys  , "ssc:MapEntry"); // ssc::IntegerMapEntry

        log(ext_trace)("Completed IntegerMappingTransformation");
    }


    void from_xml(const xml_node &node, EnumerationMapEntry &obj)
    {
        log(ext_trace)("Parsing EnumerationMapEntry");

        utils::xml::get_attribute(node, obj.source  , "source"); // string
        utils::xml::get_attribute(node, obj.target  , "target"); // string

        log(ext_trace)("Completed EnumerationMapEntry");
    }


    void from_xml(const xml_node &node, EnumerationMappingTransformation &obj)
    {
        log(ext_trace)("Parsing EnumerationMappingTransformation");

        utils::xml::get_vector(node, obj.MapEntrys  , "ssc:MapEntry"); // ssc::EnumerationMapEntry

        log(ext_trace)("Completed EnumerationMappingTransformation");
    }


    void from_xml(const xml_node &node, Item &obj)
    {
        log(ext_trace)("Parsing Item");

        utils::xml::get_attribute(node, obj.name   , "name"); // string
        utils::xml::get_attribute(node, obj.value  , "value"); // int

        log(ext_trace)("Completed Item");
    }


    void from_xml(const xml_node &node, TEnumeration &obj)
    {
        log(ext_trace)("Parsing TEnumeration");

        utils::xml::get_optional_attribute(node, obj.id           , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description  , "description"); // string
        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_vector(node, obj.Item         , "ssc:Item"); // ssc::Item
        utils::xml::get_optional_class(node, obj.Annotations  , "ssc:Annotations"); // ssc::TAnnotations

        log(ext_trace)("Completed TEnumeration");
    }


    void from_xml(const xml_node &node, TEnumerations &obj)
    {
        log(ext_trace)("Parsing TEnumerations");

        utils::xml::get_vector(node, obj.Enumerations  , "ssc:TEnumeration"); // ssc::TEnumeration

        log(ext_trace)("Completed TEnumerations");
    }


    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        log(ext_trace)("Parsing BaseUnit");

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

        log(ext_trace)("Completed BaseUnit");
    }


    void from_xml(const xml_node &node, TUnit &obj)
    {
        log(ext_trace)("Parsing TUnit");

        utils::xml::get_optional_attribute(node, obj.id           , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description  , "description"); // string
        utils::xml::get_attribute(node, obj.name         , "name"); // string
        utils::xml::get_class(node, obj.BaseUnit     , "BaseUnit"); // ssc::BaseUnit
        utils::xml::get_optional_class(node, obj.Annotations  , "ssc:Annotations"); // ssc::TAnnotations

        log(ext_trace)("Completed TUnit");
    }


    void from_xml(const xml_node &node, TUnits &obj)
    {
        log(ext_trace)("Parsing TUnits");

        utils::xml::get_vector(node, obj.Units  , "Unit"); // ssc::TUnit

        log(ext_trace)("Completed TUnits");
    }


    void from_xml(const xml_node &node, GTypeReal &obj)
    {
        log(ext_trace)("Parsing GTypeReal");

        utils::xml::get_optional_attribute(node, obj.unit  , "unit"); // string

        log(ext_trace)("Completed GTypeReal");
    }


    void from_xml(const xml_node &node, GTypeInteger &obj)
    {
        log(ext_trace)("Parsing GTypeInteger");



        log(ext_trace)("Completed GTypeInteger");
    }


    void from_xml(const xml_node &node, GTypeBoolean &obj)
    {
        log(ext_trace)("Parsing GTypeBoolean");



        log(ext_trace)("Completed GTypeBoolean");
    }


    void from_xml(const xml_node &node, GTypeString &obj)
    {
        log(ext_trace)("Parsing GTypeString");



        log(ext_trace)("Completed GTypeString");
    }


    void from_xml(const xml_node &node, GTypeEnumeration &obj)
    {
        log(ext_trace)("Parsing GTypeEnumeration");

        utils::xml::get_optional_attribute(node, obj.name  , "name"); // string

        log(ext_trace)("Completed GTypeEnumeration");
    }


    void from_xml(const xml_node &node, GTypeBinary &obj)
    {
        log(ext_trace)("Parsing GTypeBinary");

        utils::xml::get_optional_attribute(node, obj.mime_type  , "mime-type"); // string

        log(ext_trace)("Completed GTypeBinary");
    }

}
