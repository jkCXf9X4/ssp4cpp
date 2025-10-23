

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
        

        utils::xml::parse_xml(node, obj.SignalDictionaries  , "ssd:SignalDictionary");

        log(ext_trace)("Completed TSignalDictionaries");
    }


    void from_xml(const xml_node &node, ParameterMapping &obj)
    {
        log(ext_trace)("Parsing ParameterMapping");
        

        utils::xml::parse_xml(node, obj.id                , "id");
        utils::xml::parse_xml(node, obj.description       , "description");
        utils::xml::parse_xml(node, obj.type              , "type");
        utils::xml::parse_xml(node, obj.source            , "source");
        utils::xml::parse_xml(node, obj.sourceBase        , "sourceBase");
        utils::xml::parse_xml(node, obj.ParameterMapping  , "ssm:ParameterMapping");

        log(ext_trace)("Completed ParameterMapping");
    }


    void from_xml(const xml_node &node, ParameterBinding &obj)
    {
        log(ext_trace)("Parsing ParameterBinding");
        

        utils::xml::parse_xml(node, obj.id                , "id");
        utils::xml::parse_xml(node, obj.description       , "description");
        utils::xml::parse_xml(node, obj.type              , "type");
        utils::xml::parse_xml(node, obj.source            , "source");
        utils::xml::parse_xml(node, obj.sourceBase        , "sourceBase");
        utils::xml::parse_xml(node, obj.prefix            , "prefix");
        utils::xml::parse_xml(node, obj.ParameterValues   , "ssv:ParameterValues");
        utils::xml::parse_xml(node, obj.ParameterMapping  , "ssd:ParameterMapping");

        log(ext_trace)("Completed ParameterBinding");
    }


    void from_xml(const xml_node &node, TParameterBindings &obj)
    {
        log(ext_trace)("Parsing TParameterBindings");
        

        utils::xml::parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBinding");

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
        

        utils::xml::parse_xml(node, obj.startTime    , "startTime");
        utils::xml::parse_xml(node, obj.stopTime     , "stopTime");
        utils::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        log(ext_trace)("Completed TDefaultExperiment");
    }


    void from_xml(const xml_node &node, Connection &obj)
    {
        log(ext_trace)("Parsing Connection");
        log(warning)("Experimental feature information_delay used");


        utils::xml::parse_xml(node, obj.id                                , "id");
        utils::xml::parse_xml(node, obj.description                       , "description");
        utils::xml::parse_xml(node, obj.startElement                      , "startElement");
        utils::xml::parse_xml(node, obj.startConnector                    , "startConnector");
        utils::xml::parse_xml(node, obj.endElement                        , "endElement");
        utils::xml::parse_xml(node, obj.endConnector                      , "endConnector");
        utils::xml::parse_xml(node, obj.suppressUnitConversion            , "suppressUnitConversion");
        utils::xml::parse_xml(node, obj.LinearTransformation              , "ssc:LinearTransformation");
        utils::xml::parse_xml(node, obj.BooleanMappingTransformation      , "ssc:BooleanMappingTransformation");
        utils::xml::parse_xml(node, obj.IntegerMappingTransformation      , "ssc:IntegerMappingTransformation");
        utils::xml::parse_xml(node, obj.EnumerationMappingTransformation  , "ssc:EnumerationMappingTransformation");
        utils::xml::parse_xml(node, obj.ConnectionGeometry                , "ssd:ConnectionGeometry");
        utils::xml::parse_xml(node, obj.Annotations                       , "ssc:Annotations");
        utils::xml::parse_xml(node, obj.information_delay                 , "information_delay");

        log(ext_trace)("Completed Connection");
    }


    void from_xml(const xml_node &node, Connections &obj)
    {
        log(ext_trace)("Parsing Connections");
        

        utils::xml::parse_xml(node, obj.Connections  , "ssd:Connection");

        log(ext_trace)("Completed Connections");
    }


    void from_xml(const xml_node &node, Connector &obj)
    {
        log(ext_trace)("Parsing Connector");
        

        utils::xml::parse_xml(node, obj.id                 , "id");
        utils::xml::parse_xml(node, obj.description        , "description");
        utils::xml::parse_xml(node, obj.name               , "name");
        utils::xml::parse_xml(node, obj.kind               , "kind");
        utils::xml::parse_xml(node, obj.Real               , "ssc:Real");
        utils::xml::parse_xml(node, obj.Integer            , "ssc:Integer");
        utils::xml::parse_xml(node, obj.Boolean            , "ssc:Boolean");
        utils::xml::parse_xml(node, obj.String             , "ssc:String");
        utils::xml::parse_xml(node, obj.Enumeration        , "ssc:Enumeration");
        utils::xml::parse_xml(node, obj.Binary             , "ssc:Binary");
        utils::xml::parse_xml(node, obj.ConnectorGeometry  , "ssd:ConnectorGeometry");
        utils::xml::parse_xml(node, obj.Annotations        , "ssc:Annotations");

        log(ext_trace)("Completed Connector");
    }


    void from_xml(const xml_node &node, TConnectors &obj)
    {
        log(ext_trace)("Parsing TConnectors");
        

        utils::xml::parse_xml(node, obj.Connectors  , "ssd:Connector");

        log(ext_trace)("Completed TConnectors");
    }


    void from_xml(const xml_node &node, TComponent &obj)
    {
        log(ext_trace)("Parsing TComponent");
        

        utils::xml::parse_xml(node, obj.id                 , "id");
        utils::xml::parse_xml(node, obj.description        , "description");
        utils::xml::parse_xml(node, obj.name               , "name");
        utils::xml::parse_xml(node, obj.Connectors         , "ssd:Connectors");
        utils::xml::parse_xml(node, obj.ElementGeometry    , "ssd:ElementGeometry");
        utils::xml::parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBindings");
        utils::xml::parse_xml(node, obj.type               , "type");
        utils::xml::parse_xml(node, obj.source             , "source");
        utils::xml::parse_xml(node, obj.implementation     , "implementation");
        utils::xml::parse_xml(node, obj.Annotations        , "ssc:Annotations");

        log(ext_trace)("Completed TComponent");
    }


    void from_xml(const xml_node &node, TSignalDictionaryReference &obj)
    {
        log(ext_trace)("Parsing TSignalDictionaryReference");
        

        utils::xml::parse_xml(node, obj.id                 , "id");
        utils::xml::parse_xml(node, obj.description        , "description");
        utils::xml::parse_xml(node, obj.name               , "name");
        utils::xml::parse_xml(node, obj.Connectors         , "ssd:Connectors");
        utils::xml::parse_xml(node, obj.ElementGeometry    , "ssd:ElementGeometry");
        utils::xml::parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBindings");
        utils::xml::parse_xml(node, obj.dictionary         , "dictionary");
        utils::xml::parse_xml(node, obj.Annotations        , "ssc:Annotations");

        log(ext_trace)("Completed TSignalDictionaryReference");
    }


    void from_xml(const xml_node &node, Elements &obj)
    {
        log(ext_trace)("Parsing Elements");
        

        utils::xml::parse_xml(node, obj.Components                  , "ssd:Component");
        utils::xml::parse_xml(node, obj.SignalDictionaryReferences  , "ssd:SignalDictionaryReference");
        utils::xml::parse_xml(node, obj.Systems                     , "ssd:System");

        log(ext_trace)("Completed Elements");
    }


    void from_xml(const xml_node &node, TSystem &obj)
    {
        log(ext_trace)("Parsing TSystem");
        

        utils::xml::parse_xml(node, obj.id                  , "id");
        utils::xml::parse_xml(node, obj.description         , "description");
        utils::xml::parse_xml(node, obj.name                , "name");
        utils::xml::parse_xml(node, obj.Connectors          , "ssd:Connectors");
        utils::xml::parse_xml(node, obj.ElementGeometry     , "ssd:ElementGeometry");
        utils::xml::parse_xml(node, obj.ParameterBindings   , "ssd:ParameterBindings");
        utils::xml::parse_xml(node, obj.Elements            , "ssd:Elements");
        utils::xml::parse_xml(node, obj.Connections         , "ssd:Connections");
        utils::xml::parse_xml(node, obj.SignalDictionaries  , "ssd:SignalDictionaries");
        utils::xml::parse_xml(node, obj.SystemGeometry      , "ssd:SystemGeometry");
        utils::xml::parse_xml(node, obj.GraphicalElements   , "ssd:GraphicalElements");
        utils::xml::parse_xml(node, obj.Annotations         , "ssc:Annotations");

        log(ext_trace)("Completed TSystem");
    }


    void from_xml(const xml_node &node, SystemStructureDescription &obj)
    {
        log(ext_trace)("Parsing SystemStructureDescription");
        

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
        utils::xml::parse_xml(node, obj.System                 , "ssd:System");
        utils::xml::parse_xml(node, obj.Enumerations           , "ssc:Enumerations");
        utils::xml::parse_xml(node, obj.Units                  , "ssc:Units");
        utils::xml::parse_xml(node, obj.DefaultExperiment      , "ssd:DefaultExperiment");
        utils::xml::parse_xml(node, obj.Annotations            , "ssc:Annotations");

        log(ext_trace)("Completed SystemStructureDescription");
    }

}
