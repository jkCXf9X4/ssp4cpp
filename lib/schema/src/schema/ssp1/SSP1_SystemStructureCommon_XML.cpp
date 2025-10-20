

// This is a generated file, do not alter
// it is based on ssp1_ssc.toml

#include "SSP1_SystemStructureCommon_XML.hpp"


#include "xml_deserialize.hpp"

#include "utils/log.hpp"

namespace ssp4cpp::ssp1::ssc
{
    using namespace pugi;

    auto log = utils::Logger("ssp4cpp.ssp1.ssc", utils::LogLevel::info);


    void from_xml(const xml_node &node, Annotation &obj)
    {
        log.ext_trace("Parsing Annotation");
        

        utils::xml::parse_xml(node, obj.type  , "type");
        utils::xml::parse_xml(node, obj.any   , "any");

        log.ext_trace("Completed Annotation");
    }


    void from_xml(const xml_node &node, TAnnotations &obj)
    {
        log.ext_trace("Parsing TAnnotations");
        

        utils::xml::parse_xml(node, obj.Annotations  , "Annotation");

        log.ext_trace("Completed TAnnotations");
    }


    void from_xml(const xml_node &node, LinearTransformation &obj)
    {
        log.ext_trace("Parsing LinearTransformation");
        

        utils::xml::parse_xml(node, obj.factor  , "factor");
        utils::xml::parse_xml(node, obj.offset  , "offset");

        log.ext_trace("Completed LinearTransformation");
    }


    void from_xml(const xml_node &node, BooleanMapEntry &obj)
    {
        log.ext_trace("Parsing BooleanMapEntry");
        

        utils::xml::parse_xml(node, obj.source  , "source");
        utils::xml::parse_xml(node, obj.target  , "target");

        log.ext_trace("Completed BooleanMapEntry");
    }


    void from_xml(const xml_node &node, BooleanMappingTransformation &obj)
    {
        log.ext_trace("Parsing BooleanMappingTransformation");
        

        utils::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        log.ext_trace("Completed BooleanMappingTransformation");
    }


    void from_xml(const xml_node &node, IntegerMapEntry &obj)
    {
        log.ext_trace("Parsing IntegerMapEntry");
        

        utils::xml::parse_xml(node, obj.source  , "source");
        utils::xml::parse_xml(node, obj.target  , "target");

        log.ext_trace("Completed IntegerMapEntry");
    }


    void from_xml(const xml_node &node, IntegerMappingTransformation &obj)
    {
        log.ext_trace("Parsing IntegerMappingTransformation");
        

        utils::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        log.ext_trace("Completed IntegerMappingTransformation");
    }


    void from_xml(const xml_node &node, EnumerationMapEntry &obj)
    {
        log.ext_trace("Parsing EnumerationMapEntry");
        

        utils::xml::parse_xml(node, obj.source  , "source");
        utils::xml::parse_xml(node, obj.target  , "target");

        log.ext_trace("Completed EnumerationMapEntry");
    }


    void from_xml(const xml_node &node, EnumerationMappingTransformation &obj)
    {
        log.ext_trace("Parsing EnumerationMappingTransformation");
        

        utils::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        log.ext_trace("Completed EnumerationMappingTransformation");
    }


    void from_xml(const xml_node &node, Item &obj)
    {
        log.ext_trace("Parsing Item");
        

        utils::xml::parse_xml(node, obj.name   , "name");
        utils::xml::parse_xml(node, obj.value  , "value");

        log.ext_trace("Completed Item");
    }


    void from_xml(const xml_node &node, TEnumeration &obj)
    {
        log.ext_trace("Parsing TEnumeration");
        

        utils::xml::parse_xml(node, obj.id           , "id");
        utils::xml::parse_xml(node, obj.description  , "description");
        utils::xml::parse_xml(node, obj.name         , "name");
        utils::xml::parse_xml(node, obj.Item         , "ssc:Item");
        utils::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        log.ext_trace("Completed TEnumeration");
    }


    void from_xml(const xml_node &node, TEnumerations &obj)
    {
        log.ext_trace("Parsing TEnumerations");
        

        utils::xml::parse_xml(node, obj.Enumerations  , "ssc:TEnumeration");

        log.ext_trace("Completed TEnumerations");
    }


    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        log.ext_trace("Parsing BaseUnit");
        

        utils::xml::parse_xml(node, obj.kg      , "kg");
        utils::xml::parse_xml(node, obj.m       , "m");
        utils::xml::parse_xml(node, obj.s       , "s");
        utils::xml::parse_xml(node, obj.a       , "a");
        utils::xml::parse_xml(node, obj.k       , "k");
        utils::xml::parse_xml(node, obj.mol     , "mol");
        utils::xml::parse_xml(node, obj.cd      , "cd");
        utils::xml::parse_xml(node, obj.rad     , "rad");
        utils::xml::parse_xml(node, obj.factor  , "factor");
        utils::xml::parse_xml(node, obj.offset  , "offset");

        log.ext_trace("Completed BaseUnit");
    }


    void from_xml(const xml_node &node, TUnit &obj)
    {
        log.ext_trace("Parsing TUnit");
        

        utils::xml::parse_xml(node, obj.id           , "id");
        utils::xml::parse_xml(node, obj.description  , "description");
        utils::xml::parse_xml(node, obj.name         , "name");
        utils::xml::parse_xml(node, obj.BaseUnit     , "BaseUnit");
        utils::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        log.ext_trace("Completed TUnit");
    }


    void from_xml(const xml_node &node, TUnits &obj)
    {
        log.ext_trace("Parsing TUnits");
        

        utils::xml::parse_xml(node, obj.Units  , "Unit");

        log.ext_trace("Completed TUnits");
    }


    void from_xml(const xml_node &node, GTypeReal &obj)
    {
        log.ext_trace("Parsing GTypeReal");
        

        utils::xml::parse_xml(node, obj.unit  , "unit");

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
        

        utils::xml::parse_xml(node, obj.name  , "name");

        log.ext_trace("Completed GTypeEnumeration");
    }


    void from_xml(const xml_node &node, GTypeBinary &obj)
    {
        log.ext_trace("Parsing GTypeBinary");
        

        utils::xml::parse_xml(node, obj.mime_type  , "mime-type");

        log.ext_trace("Completed GTypeBinary");
    }

}
