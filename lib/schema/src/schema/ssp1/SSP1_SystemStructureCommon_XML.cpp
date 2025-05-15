

// This is a generated file, do not alter
// it is based on ssp1_ssc.toml

#include "SSP1_SystemStructureCommon_XML.hpp"


#include "xml_deserialize.hpp"

#include "common_log.hpp"

namespace ssp4cpp::ssp1::ssc
{
    using namespace pugi;
    using namespace common;

    auto log = Logger("ssp4cpp.ssp1.ssc", LogLevel::info);


    void from_xml(const xml_node &node, Annotation &obj)
    {
        log.ext_trace("Parsing Annotation");

        ssp4cpp::common::xml::parse_xml(node, obj.type  , "type");
        ssp4cpp::common::xml::parse_xml(node, obj.any   , "any");

        log.ext_trace("Completed Annotation");
    }


    void from_xml(const xml_node &node, TAnnotations &obj)
    {
        log.ext_trace("Parsing TAnnotations");

        ssp4cpp::common::xml::parse_xml(node, obj.Annotations  , "Annotation");

        log.ext_trace("Completed TAnnotations");
    }


    void from_xml(const xml_node &node, LinearTransformation &obj)
    {
        log.ext_trace("Parsing LinearTransformation");

        ssp4cpp::common::xml::parse_xml(node, obj.factor  , "factor");
        ssp4cpp::common::xml::parse_xml(node, obj.offset  , "offset");

        log.ext_trace("Completed LinearTransformation");
    }


    void from_xml(const xml_node &node, BooleanMapEntry &obj)
    {
        log.ext_trace("Parsing BooleanMapEntry");

        ssp4cpp::common::xml::parse_xml(node, obj.source  , "source");
        ssp4cpp::common::xml::parse_xml(node, obj.target  , "target");

        log.ext_trace("Completed BooleanMapEntry");
    }


    void from_xml(const xml_node &node, BooleanMappingTransformation &obj)
    {
        log.ext_trace("Parsing BooleanMappingTransformation");

        ssp4cpp::common::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        log.ext_trace("Completed BooleanMappingTransformation");
    }


    void from_xml(const xml_node &node, IntegerMapEntry &obj)
    {
        log.ext_trace("Parsing IntegerMapEntry");

        ssp4cpp::common::xml::parse_xml(node, obj.source  , "source");
        ssp4cpp::common::xml::parse_xml(node, obj.target  , "target");

        log.ext_trace("Completed IntegerMapEntry");
    }


    void from_xml(const xml_node &node, IntegerMappingTransformation &obj)
    {
        log.ext_trace("Parsing IntegerMappingTransformation");

        ssp4cpp::common::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        log.ext_trace("Completed IntegerMappingTransformation");
    }


    void from_xml(const xml_node &node, EnumerationMapEntry &obj)
    {
        log.ext_trace("Parsing EnumerationMapEntry");

        ssp4cpp::common::xml::parse_xml(node, obj.source  , "source");
        ssp4cpp::common::xml::parse_xml(node, obj.target  , "target");

        log.ext_trace("Completed EnumerationMapEntry");
    }


    void from_xml(const xml_node &node, EnumerationMappingTransformation &obj)
    {
        log.ext_trace("Parsing EnumerationMappingTransformation");

        ssp4cpp::common::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        log.ext_trace("Completed EnumerationMappingTransformation");
    }


    void from_xml(const xml_node &node, Item &obj)
    {
        log.ext_trace("Parsing Item");

        ssp4cpp::common::xml::parse_xml(node, obj.name   , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.value  , "value");

        log.ext_trace("Completed Item");
    }


    void from_xml(const xml_node &node, TEnumeration &obj)
    {
        log.ext_trace("Parsing TEnumeration");

        ssp4cpp::common::xml::parse_xml(node, obj.id           , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description  , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.Item         , "ssc:Item");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        log.ext_trace("Completed TEnumeration");
    }


    void from_xml(const xml_node &node, TEnumerations &obj)
    {
        log.ext_trace("Parsing TEnumerations");

        ssp4cpp::common::xml::parse_xml(node, obj.Enumerations  , "ssc:TEnumeration");

        log.ext_trace("Completed TEnumerations");
    }


    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        log.ext_trace("Parsing BaseUnit");

        ssp4cpp::common::xml::parse_xml(node, obj.kg      , "kg");
        ssp4cpp::common::xml::parse_xml(node, obj.m       , "m");
        ssp4cpp::common::xml::parse_xml(node, obj.s       , "s");
        ssp4cpp::common::xml::parse_xml(node, obj.a       , "a");
        ssp4cpp::common::xml::parse_xml(node, obj.k       , "k");
        ssp4cpp::common::xml::parse_xml(node, obj.mol     , "mol");
        ssp4cpp::common::xml::parse_xml(node, obj.cd      , "cd");
        ssp4cpp::common::xml::parse_xml(node, obj.rad     , "rad");
        ssp4cpp::common::xml::parse_xml(node, obj.factor  , "factor");
        ssp4cpp::common::xml::parse_xml(node, obj.offset  , "offset");

        log.ext_trace("Completed BaseUnit");
    }


    void from_xml(const xml_node &node, TUnit &obj)
    {
        log.ext_trace("Parsing TUnit");

        ssp4cpp::common::xml::parse_xml(node, obj.id           , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description  , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.BaseUnit     , "ssc:BaseUnit");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        log.ext_trace("Completed TUnit");
    }


    void from_xml(const xml_node &node, TUnits &obj)
    {
        log.ext_trace("Parsing TUnits");

        ssp4cpp::common::xml::parse_xml(node, obj.Units  , "ssc:Unit");

        log.ext_trace("Completed TUnits");
    }


    void from_xml(const xml_node &node, GTypeReal &obj)
    {
        log.ext_trace("Parsing GTypeReal");

        ssp4cpp::common::xml::parse_xml(node, obj.unit  , "unit");

        log.ext_trace("Completed GTypeReal");
    }


    void from_xml(const xml_node &node, GTypeInteger &obj)
    {
        log.ext_trace("Parsing GTypeInteger");



        log.ext_trace("Completed GTypeInteger");
    }


    void from_xml(const xml_node &node, GTypeBoolean &obj)
    {
        log.ext_trace("Parsing GTypeBoolean");



        log.ext_trace("Completed GTypeBoolean");
    }


    void from_xml(const xml_node &node, GTypeString &obj)
    {
        log.ext_trace("Parsing GTypeString");



        log.ext_trace("Completed GTypeString");
    }


    void from_xml(const xml_node &node, GTypeEnumeration &obj)
    {
        log.ext_trace("Parsing GTypeEnumeration");

        ssp4cpp::common::xml::parse_xml(node, obj.name  , "name");

        log.ext_trace("Completed GTypeEnumeration");
    }


    void from_xml(const xml_node &node, GTypeBinary &obj)
    {
        log.ext_trace("Parsing GTypeBinary");

        ssp4cpp::common::xml::parse_xml(node, obj.mime_type  , "mime-type");

        log.ext_trace("Completed GTypeBinary");
    }

}
