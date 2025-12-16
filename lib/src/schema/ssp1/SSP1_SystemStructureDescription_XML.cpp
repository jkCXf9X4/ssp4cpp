

// This is a generated file, do not alter
// it is based on ssp1_ssd.toml

#include "SSP1_SystemStructureDescription_XML.hpp"
#include "SSP1_SystemStructureCommon_XML.hpp"
#include "SSP1_SystemStructureParameterMapping_XML.hpp"
#include "SSP1_SystemStructureParameterValues_XML.hpp"

#include "xml_deserialize.hpp"

#include "cutecpp/log.hpp"

namespace ssp4cpp::ssp1::ssd
{
    using namespace pugi;

    auto log = Logger("ssp4cpp.ssp1.ssd", LogLevel::info);


    void from_xml(const xml_node &node, SystemGeometry &obj)
    {
        log(ext_trace)("Parsing SystemGeometry");



        log(ext_trace)("Completed SystemGeometry");
    }


    void from_xml(const xml_node &node, ConnectorGeometry &obj)
    {
        log(ext_trace)("Parsing ConnectorGeometry");



        log(ext_trace)("Completed ConnectorGeometry");
    }


    void from_xml(const xml_node &node, ElementGeometry &obj)
    {
        log(ext_trace)("Parsing ElementGeometry");



        log(ext_trace)("Completed ElementGeometry");
    }


    void from_xml(const xml_node &node, ConnectionGeometry &obj)
    {
        log(ext_trace)("Parsing ConnectionGeometry");



        log(ext_trace)("Completed ConnectionGeometry");
    }


    void from_xml(const xml_node &node, SignalDictionary &obj)
    {
        log(ext_trace)("Parsing SignalDictionary");



        log(ext_trace)("Completed SignalDictionary");
    }


    void from_xml(const xml_node &node, TSignalDictionaries &obj)
    {
        log(ext_trace)("Parsing TSignalDictionaries");

        utils::xml::get_vector(node, obj.SignalDictionaries  , "ssd:SignalDictionary"); // ssd::SignalDictionary

        log(ext_trace)("Completed TSignalDictionaries");
    }


    void from_xml(const xml_node &node, ParameterMapping &obj)
    {
        log(ext_trace)("Parsing ParameterMapping");

        utils::xml::get_optional_attribute(node, obj.id                , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description       , "description"); // string
        utils::xml::get_optional_attribute(node, obj.type              , "type"); // string
        utils::xml::get_optional_attribute(node, obj.source            , "source"); // string
        utils::xml::get_optional_attribute(node, obj.sourceBase        , "sourceBase"); // string
        utils::xml::get_optional_class(node, obj.ParameterMapping  , "ssm:ParameterMapping"); // ssm::ParameterMapping

        log(ext_trace)("Completed ParameterMapping");
    }


    void from_xml(const xml_node &node, ParameterBinding &obj)
    {
        log(ext_trace)("Parsing ParameterBinding");

        utils::xml::get_optional_attribute(node, obj.id                , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description       , "description"); // string
        utils::xml::get_optional_attribute(node, obj.type              , "type"); // string
        utils::xml::get_optional_attribute(node, obj.source            , "source"); // string
        utils::xml::get_optional_attribute(node, obj.sourceBase        , "sourceBase"); // string
        utils::xml::get_optional_attribute(node, obj.prefix            , "prefix"); // string
        utils::xml::get_optional_class(node, obj.ParameterValues   , "ssv:ParameterValues"); // ssv::ParameterSet
        utils::xml::get_optional_class(node, obj.ParameterMapping  , "ssd:ParameterMapping"); // ssd::ParameterMapping

        log(ext_trace)("Completed ParameterBinding");
    }


    void from_xml(const xml_node &node, TParameterBindings &obj)
    {
        log(ext_trace)("Parsing TParameterBindings");

        utils::xml::get_vector(node, obj.ParameterBindings  , "ssd:ParameterBinding"); // ssd::ParameterBinding

        log(ext_trace)("Completed TParameterBindings");
    }


    void from_xml(const xml_node &node, GraphicalElements &obj)
    {
        log(ext_trace)("Parsing GraphicalElements");



        log(ext_trace)("Completed GraphicalElements");
    }


    void from_xml(const xml_node &node, TDefaultExperiment &obj)
    {
        log(ext_trace)("Parsing TDefaultExperiment");

        utils::xml::get_optional_attribute(node, obj.startTime    , "startTime"); // double
        utils::xml::get_optional_attribute(node, obj.stopTime     , "stopTime"); // double
        utils::xml::get_optional_class(node, obj.Annotations  , "ssc:Annotations"); // ssc::TAnnotations

        log(ext_trace)("Completed TDefaultExperiment");
    }


    void from_xml(const xml_node &node, Connection &obj)
    {
        log(ext_trace)("Parsing Connection");

        utils::xml::get_optional_attribute(node, obj.id                                , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description                       , "description"); // string
        utils::xml::get_optional_attribute(node, obj.startElement                      , "startElement"); // string
        utils::xml::get_attribute(node, obj.startConnector                    , "startConnector"); // string
        utils::xml::get_optional_attribute(node, obj.endElement                        , "endElement"); // string
        utils::xml::get_attribute(node, obj.endConnector                      , "endConnector"); // string
        utils::xml::get_optional_attribute(node, obj.suppressUnitConversion            , "suppressUnitConversion"); // bool
        utils::xml::get_optional_class(node, obj.LinearTransformation              , "ssc:LinearTransformation"); // ssc::LinearTransformation
        utils::xml::get_optional_class(node, obj.BooleanMappingTransformation      , "ssc:BooleanMappingTransformation"); // ssc::BooleanMappingTransformation
        utils::xml::get_optional_class(node, obj.IntegerMappingTransformation      , "ssc:IntegerMappingTransformation"); // ssc::IntegerMappingTransformation
        utils::xml::get_optional_class(node, obj.EnumerationMappingTransformation  , "ssc:EnumerationMappingTransformation"); // ssc::EnumerationMappingTransformation
        utils::xml::get_optional_class(node, obj.ConnectionGeometry                , "ssd:ConnectionGeometry"); // ssd::ConnectionGeometry
        utils::xml::get_optional_class(node, obj.Annotations                       , "ssc:Annotations"); // ssc::TAnnotations

        log(ext_trace)("Completed Connection");
    }


    void from_xml(const xml_node &node, Connections &obj)
    {
        log(ext_trace)("Parsing Connections");

        utils::xml::get_vector(node, obj.Connections  , "ssd:Connection"); // ssd::Connection

        log(ext_trace)("Completed Connections");
    }


    void from_xml(const xml_node &node, Connector &obj)
    {
        log(ext_trace)("Parsing Connector");

        utils::xml::get_optional_attribute(node, obj.id                 , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description        , "description"); // string
        utils::xml::get_attribute(node, obj.name               , "name"); // string
        utils::xml::get_enum(node, obj.kind               , "kind"); // fmi2::md::Causality
        utils::xml::get_optional_class(node, obj.Real               , "ssc:Real"); // ssc::GTypeReal
        utils::xml::get_optional_class(node, obj.Integer            , "ssc:Integer"); // ssc::GTypeInteger
        utils::xml::get_optional_class(node, obj.Boolean            , "ssc:Boolean"); // ssc::GTypeBoolean
        utils::xml::get_optional_class(node, obj.String             , "ssc:String"); // ssc::GTypeString
        utils::xml::get_optional_class(node, obj.Enumeration        , "ssc:Enumeration"); // ssc::GTypeEnumeration
        utils::xml::get_optional_class(node, obj.Binary             , "ssc:Binary"); // ssc::GTypeBinary
        utils::xml::get_optional_class(node, obj.ConnectorGeometry  , "ssd:ConnectorGeometry"); // ssd::ConnectorGeometry
        utils::xml::get_optional_class(node, obj.Annotations        , "ssc:Annotations"); // ssc::TAnnotations

        log(ext_trace)("Completed Connector");
    }


    void from_xml(const xml_node &node, TConnectors &obj)
    {
        log(ext_trace)("Parsing TConnectors");

        utils::xml::get_vector(node, obj.Connectors  , "ssd:Connector"); // ssd::Connector

        log(ext_trace)("Completed TConnectors");
    }


    void from_xml(const xml_node &node, TComponent &obj)
    {
        log(ext_trace)("Parsing TComponent");

        utils::xml::get_optional_attribute(node, obj.id                 , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description        , "description"); // string
        utils::xml::get_optional_attribute(node, obj.name               , "name"); // string
        utils::xml::get_optional_class(node, obj.Connectors         , "ssd:Connectors"); // ssd::TConnectors
        utils::xml::get_optional_class(node, obj.ElementGeometry    , "ssd:ElementGeometry"); // ssd::ElementGeometry
        utils::xml::get_optional_class(node, obj.ParameterBindings  , "ssd:ParameterBindings"); // ssd::TParameterBindings
        utils::xml::get_optional_enum(node, obj.type               , "type"); // ssd::ComponentType
        utils::xml::get_attribute(node, obj.source             , "source"); // string
        utils::xml::get_optional_attribute(node, obj.implementation     , "implementation"); // string
        utils::xml::get_optional_class(node, obj.Annotations        , "ssc:Annotations"); // ssc::TAnnotations

        log(ext_trace)("Completed TComponent");
    }


    void from_xml(const xml_node &node, TSignalDictionaryReference &obj)
    {
        log(ext_trace)("Parsing TSignalDictionaryReference");

        utils::xml::get_optional_attribute(node, obj.id                 , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description        , "description"); // string
        utils::xml::get_optional_attribute(node, obj.name               , "name"); // string
        utils::xml::get_optional_class(node, obj.Connectors         , "ssd:Connectors"); // ssd::TConnectors
        utils::xml::get_optional_class(node, obj.ElementGeometry    , "ssd:ElementGeometry"); // ssd::ElementGeometry
        utils::xml::get_optional_class(node, obj.ParameterBindings  , "ssd:ParameterBindings"); // ssd::TParameterBindings
        utils::xml::get_attribute(node, obj.dictionary         , "dictionary"); // string
        utils::xml::get_optional_class(node, obj.Annotations        , "ssc:Annotations"); // ssc::TAnnotations

        log(ext_trace)("Completed TSignalDictionaryReference");
    }


    void from_xml(const xml_node &node, Elements &obj)
    {
        log(ext_trace)("Parsing Elements");

        utils::xml::get_vector(node, obj.Components                  , "ssd:Component"); // ssd::TComponent
        utils::xml::get_vector(node, obj.SignalDictionaryReferences  , "ssd:SignalDictionaryReference"); // ssd::TSignalDictionaryReference
        utils::xml::get_vector(node, obj.Systems                     , "ssd:System"); // ssd::TSystem

        log(ext_trace)("Completed Elements");
    }


    void from_xml(const xml_node &node, TSystem &obj)
    {
        log(ext_trace)("Parsing TSystem");

        utils::xml::get_optional_attribute(node, obj.id                  , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description         , "description"); // string
        utils::xml::get_optional_attribute(node, obj.name                , "name"); // string
        utils::xml::get_optional_class(node, obj.Connectors          , "ssd:Connectors"); // ssd::TConnectors
        utils::xml::get_optional_class(node, obj.ElementGeometry     , "ssd:ElementGeometry"); // ssd::ElementGeometry
        utils::xml::get_optional_class(node, obj.ParameterBindings   , "ssd:ParameterBindings"); // ssd::TParameterBindings
        utils::xml::get_optional_class(node, obj.Elements            , "ssd:Elements"); // ssd::Elements
        utils::xml::get_optional_class(node, obj.Connections         , "ssd:Connections"); // ssd::Connections
        utils::xml::get_optional_class(node, obj.SignalDictionaries  , "ssd:SignalDictionaries"); // ssd::TSignalDictionaries
        utils::xml::get_optional_class(node, obj.SystemGeometry      , "ssd:SystemGeometry"); // ssd::SystemGeometry
        utils::xml::get_optional_class(node, obj.GraphicalElements   , "ssd:GraphicalElements"); // ssd::GraphicalElements
        utils::xml::get_optional_class(node, obj.Annotations         , "ssc:Annotations"); // ssc::TAnnotations

        log(ext_trace)("Completed TSystem");
    }


    void from_xml(const xml_node &node, SystemStructureDescription &obj)
    {
        log(ext_trace)("Parsing SystemStructureDescription");

        utils::xml::get_attribute(node, obj.version                , "version"); // string
        utils::xml::get_attribute(node, obj.name                   , "name"); // string
        utils::xml::get_optional_attribute(node, obj.id                     , "id"); // string
        utils::xml::get_optional_attribute(node, obj.description            , "description"); // string
        utils::xml::get_optional_attribute(node, obj.author                 , "author"); // string
        utils::xml::get_optional_attribute(node, obj.fileversion            , "fileversion"); // string
        utils::xml::get_optional_attribute(node, obj.copyright              , "copyright"); // string
        utils::xml::get_optional_attribute(node, obj.license                , "license"); // string
        utils::xml::get_optional_attribute(node, obj.generationTool         , "generationTool"); // string
        utils::xml::get_optional_attribute(node, obj.generationDateAndTime  , "generationDateAndTime"); // string
        utils::xml::get_class(node, obj.System                 , "ssd:System"); // ssd::TSystem
        utils::xml::get_optional_class(node, obj.Enumerations           , "ssc:Enumerations"); // ssc::TEnumerations
        utils::xml::get_optional_class(node, obj.Units                  , "ssc:Units"); // ssc::TUnits
        utils::xml::get_optional_class(node, obj.DefaultExperiment      , "ssd:DefaultExperiment"); // ssd::TDefaultExperiment
        utils::xml::get_optional_class(node, obj.Annotations            , "ssc:Annotations"); // ssc::TAnnotations

        log(ext_trace)("Completed SystemStructureDescription");
    }

}
