

// This is a generated file, do not alter
// it is based on ssp1_ssc.toml

#include "SSP1_SystemStructureCommon_XML.hpp"


#include "xml_deserialize.hpp"

#include "common_log.hpp"

namespace ssp4cpp::ssp1::ssc
{
    using namespace pugi;
    using namespace common;


    void from_xml(const xml_node &node, Annotation &obj)
    {
        Logger::trace("Parsing Annotation");

        ssp4cpp::common::xml::parse_xml(node, obj.type  , "type");
        ssp4cpp::common::xml::parse_xml(node, obj.any   , "any");

        Logger::trace("Completed Annotation");
    }


    void from_xml(const xml_node &node, TAnnotations &obj)
    {
        Logger::trace("Parsing TAnnotations");

        ssp4cpp::common::xml::parse_xml(node, obj.Annotations  , "Annotation");

        Logger::trace("Completed TAnnotations");
    }


    void from_xml(const xml_node &node, LinearTransformation &obj)
    {
        Logger::trace("Parsing LinearTransformation");

        ssp4cpp::common::xml::parse_xml(node, obj.factor  , "factor");
        ssp4cpp::common::xml::parse_xml(node, obj.offset  , "offset");

        Logger::trace("Completed LinearTransformation");
    }


    void from_xml(const xml_node &node, BooleanMapEntry &obj)
    {
        Logger::trace("Parsing BooleanMapEntry");

        ssp4cpp::common::xml::parse_xml(node, obj.source  , "source");
        ssp4cpp::common::xml::parse_xml(node, obj.target  , "target");

        Logger::trace("Completed BooleanMapEntry");
    }


    void from_xml(const xml_node &node, BooleanMappingTransformation &obj)
    {
        Logger::trace("Parsing BooleanMappingTransformation");

        ssp4cpp::common::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        Logger::trace("Completed BooleanMappingTransformation");
    }


    void from_xml(const xml_node &node, IntegerMapEntry &obj)
    {
        Logger::trace("Parsing IntegerMapEntry");

        ssp4cpp::common::xml::parse_xml(node, obj.source  , "source");
        ssp4cpp::common::xml::parse_xml(node, obj.target  , "target");

        Logger::trace("Completed IntegerMapEntry");
    }


    void from_xml(const xml_node &node, IntegerMappingTransformation &obj)
    {
        Logger::trace("Parsing IntegerMappingTransformation");

        ssp4cpp::common::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        Logger::trace("Completed IntegerMappingTransformation");
    }


    void from_xml(const xml_node &node, EnumerationMapEntry &obj)
    {
        Logger::trace("Parsing EnumerationMapEntry");

        ssp4cpp::common::xml::parse_xml(node, obj.source  , "source");
        ssp4cpp::common::xml::parse_xml(node, obj.target  , "target");

        Logger::trace("Completed EnumerationMapEntry");
    }


    void from_xml(const xml_node &node, EnumerationMappingTransformation &obj)
    {
        Logger::trace("Parsing EnumerationMappingTransformation");

        ssp4cpp::common::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        Logger::trace("Completed EnumerationMappingTransformation");
    }


    void from_xml(const xml_node &node, Item &obj)
    {
        Logger::trace("Parsing Item");

        ssp4cpp::common::xml::parse_xml(node, obj.name   , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.value  , "value");

        Logger::trace("Completed Item");
    }


    void from_xml(const xml_node &node, TEnumeration &obj)
    {
        Logger::trace("Parsing TEnumeration");

        ssp4cpp::common::xml::parse_xml(node, obj.id           , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description  , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.Item         , "ssc:Item");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        Logger::trace("Completed TEnumeration");
    }


    void from_xml(const xml_node &node, TEnumerations &obj)
    {
        Logger::trace("Parsing TEnumerations");

        ssp4cpp::common::xml::parse_xml(node, obj.Enumerations  , "ssc:TEnumeration");

        Logger::trace("Completed TEnumerations");
    }


    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        Logger::trace("Parsing BaseUnit");

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

        Logger::trace("Completed BaseUnit");
    }


    void from_xml(const xml_node &node, TUnit &obj)
    {
        Logger::trace("Parsing TUnit");

        ssp4cpp::common::xml::parse_xml(node, obj.id           , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description  , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.BaseUnit     , "ssc:BaseUnit");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        Logger::trace("Completed TUnit");
    }


    void from_xml(const xml_node &node, TUnits &obj)
    {
        Logger::trace("Parsing TUnits");

        ssp4cpp::common::xml::parse_xml(node, obj.Units  , "ssc:Unit");

        Logger::trace("Completed TUnits");
    }


    void from_xml(const xml_node &node, GTypeReal &obj)
    {
        Logger::trace("Parsing GTypeReal");

        ssp4cpp::common::xml::parse_xml(node, obj.unit  , "unit");

        Logger::trace("Completed GTypeReal");
    }


    void from_xml(const xml_node &node, GTypeInteger &obj)
    {
        Logger::trace("Parsing GTypeInteger");



        Logger::trace("Completed GTypeInteger");
    }


    void from_xml(const xml_node &node, GTypeBoolean &obj)
    {
        Logger::trace("Parsing GTypeBoolean");



        Logger::trace("Completed GTypeBoolean");
    }


    void from_xml(const xml_node &node, GTypeString &obj)
    {
        Logger::trace("Parsing GTypeString");



        Logger::trace("Completed GTypeString");
    }


    void from_xml(const xml_node &node, GTypeEnumeration &obj)
    {
        Logger::trace("Parsing GTypeEnumeration");

        ssp4cpp::common::xml::parse_xml(node, obj.name  , "name");

        Logger::trace("Completed GTypeEnumeration");
    }


    void from_xml(const xml_node &node, GTypeBinary &obj)
    {
        Logger::trace("Parsing GTypeBinary");

        ssp4cpp::common::xml::parse_xml(node, obj.mime_type  , "mime-type");

        Logger::trace("Completed GTypeBinary");
    }

}
