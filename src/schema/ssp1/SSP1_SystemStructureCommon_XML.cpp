

// This is a generated file, do not alter
// it is based on ssp1_ssc.toml

#include "xml_deserialize.hpp"
#include "SSP1_SystemStructureCommon_XML.hpp"


using namespace std;
using namespace pugi;
using namespace ssp4cpp::xml;

#include <boost/log/trivial.hpp>

namespace ssp4cpp::ssp1::ssc
{
    using namespace pugi;


    void from_xml(const xml_node &node, Annotation &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Annotation" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.type  , "type");
        ssp4cpp::xml::parse_xml(node, obj.any   , "any");

        BOOST_LOG_TRIVIAL(trace) << "Completed Annotation" << std::endl;
    }


    void from_xml(const xml_node &node, TAnnotations &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TAnnotations" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Annotations  , "Annotation");

        BOOST_LOG_TRIVIAL(trace) << "Completed TAnnotations" << std::endl;
    }


    void from_xml(const xml_node &node, LinearTransformation &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing LinearTransformation" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.factor  , "factor");
        ssp4cpp::xml::parse_xml(node, obj.offset  , "offset");

        BOOST_LOG_TRIVIAL(trace) << "Completed LinearTransformation" << std::endl;
    }


    void from_xml(const xml_node &node, BooleanMapEntry &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing BooleanMapEntry" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.source  , "source");
        ssp4cpp::xml::parse_xml(node, obj.target  , "target");

        BOOST_LOG_TRIVIAL(trace) << "Completed BooleanMapEntry" << std::endl;
    }


    void from_xml(const xml_node &node, BooleanMappingTransformation &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing BooleanMappingTransformation" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        BOOST_LOG_TRIVIAL(trace) << "Completed BooleanMappingTransformation" << std::endl;
    }


    void from_xml(const xml_node &node, IntegerMapEntry &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing IntegerMapEntry" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.source  , "source");
        ssp4cpp::xml::parse_xml(node, obj.target  , "target");

        BOOST_LOG_TRIVIAL(trace) << "Completed IntegerMapEntry" << std::endl;
    }


    void from_xml(const xml_node &node, IntegerMappingTransformation &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing IntegerMappingTransformation" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        BOOST_LOG_TRIVIAL(trace) << "Completed IntegerMappingTransformation" << std::endl;
    }


    void from_xml(const xml_node &node, EnumerationMapEntry &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing EnumerationMapEntry" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.source  , "source");
        ssp4cpp::xml::parse_xml(node, obj.target  , "target");

        BOOST_LOG_TRIVIAL(trace) << "Completed EnumerationMapEntry" << std::endl;
    }


    void from_xml(const xml_node &node, EnumerationMappingTransformation &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing EnumerationMappingTransformation" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.MapEntrys  , "ssc:MapEntry");

        BOOST_LOG_TRIVIAL(trace) << "Completed EnumerationMappingTransformation" << std::endl;
    }


    void from_xml(const xml_node &node, Item &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Item" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.name   , "name");
        ssp4cpp::xml::parse_xml(node, obj.value  , "value");

        BOOST_LOG_TRIVIAL(trace) << "Completed Item" << std::endl;
    }


    void from_xml(const xml_node &node, TEnumeration &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TEnumeration" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.id           , "id");
        ssp4cpp::xml::parse_xml(node, obj.description  , "description");
        ssp4cpp::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::xml::parse_xml(node, obj.Item         , "ssc:Item");
        ssp4cpp::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed TEnumeration" << std::endl;
    }


    void from_xml(const xml_node &node, TEnumerations &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TEnumerations" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Enumerations  , "ssc:TEnumeration");

        BOOST_LOG_TRIVIAL(trace) << "Completed TEnumerations" << std::endl;
    }


    void from_xml(const xml_node &node, BaseUnit &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing BaseUnit" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.kg      , "kg");
        ssp4cpp::xml::parse_xml(node, obj.m       , "m");
        ssp4cpp::xml::parse_xml(node, obj.s       , "s");
        ssp4cpp::xml::parse_xml(node, obj.a       , "a");
        ssp4cpp::xml::parse_xml(node, obj.k       , "k");
        ssp4cpp::xml::parse_xml(node, obj.mol     , "mol");
        ssp4cpp::xml::parse_xml(node, obj.cd      , "cd");
        ssp4cpp::xml::parse_xml(node, obj.rad     , "rad");
        ssp4cpp::xml::parse_xml(node, obj.factor  , "factor");
        ssp4cpp::xml::parse_xml(node, obj.offset  , "offset");

        BOOST_LOG_TRIVIAL(trace) << "Completed BaseUnit" << std::endl;
    }


    void from_xml(const xml_node &node, TUnit &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TUnit" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.id           , "id");
        ssp4cpp::xml::parse_xml(node, obj.description  , "description");
        ssp4cpp::xml::parse_xml(node, obj.name         , "name");
        ssp4cpp::xml::parse_xml(node, obj.BaseUnit     , "ssc:BaseUnit");
        ssp4cpp::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed TUnit" << std::endl;
    }


    void from_xml(const xml_node &node, TUnits &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TUnits" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Units  , "ssc:Unit");

        BOOST_LOG_TRIVIAL(trace) << "Completed TUnits" << std::endl;
    }


    void from_xml(const xml_node &node, GTypeReal &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing GTypeReal" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.unit  , "unit");

        BOOST_LOG_TRIVIAL(trace) << "Completed GTypeReal" << std::endl;
    }


    void from_xml(const xml_node &node, GTypeInteger &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing GTypeInteger" << std::endl;



        BOOST_LOG_TRIVIAL(trace) << "Completed GTypeInteger" << std::endl;
    }


    void from_xml(const xml_node &node, GTypeBoolean &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing GTypeBoolean" << std::endl;



        BOOST_LOG_TRIVIAL(trace) << "Completed GTypeBoolean" << std::endl;
    }


    void from_xml(const xml_node &node, GTypeString &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing GTypeString" << std::endl;



        BOOST_LOG_TRIVIAL(trace) << "Completed GTypeString" << std::endl;
    }


    void from_xml(const xml_node &node, GTypeEnumeration &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing GTypeEnumeration" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.name  , "name");

        BOOST_LOG_TRIVIAL(trace) << "Completed GTypeEnumeration" << std::endl;
    }


    void from_xml(const xml_node &node, GTypeBinary &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing GTypeBinary" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.mime_type  , "mime-type");

        BOOST_LOG_TRIVIAL(trace) << "Completed GTypeBinary" << std::endl;
    }

}
