

// This is a generated file, do not alter
// it is based on ssp1_ssd.toml

#include "SSP1_SystemStructureDescription_XML.hpp"
#include "SSP1_SystemStructureCommon_XML.hpp"
#include "SSP1_SystemStructureParameterMapping_XML.hpp"
#include "SSP1_SystemStructureParameterValues_XML.hpp"

#include "xml_deserialize.hpp"

#include "utils/log.hpp"

namespace ssp4cpp::ssp1::ssd
{
    using namespace pugi;
    using namespace common;

    auto log = Logger("ssp4cpp.ssp1.ssd", LogLevel::info);


    void from_xml(const xml_node &node, SystemGeometry &obj)
    {
        log.ext_trace("Parsing SystemGeometry");
        


        log.ext_trace("Completed SystemGeometry");
    }


    void from_xml(const xml_node &node, ConnectorGeometry &obj)
    {
        log.ext_trace("Parsing ConnectorGeometry");
        


        log.ext_trace("Completed ConnectorGeometry");
    }


    void from_xml(const xml_node &node, ElementGeometry &obj)
    {
        log.ext_trace("Parsing ElementGeometry");
        


        log.ext_trace("Completed ElementGeometry");
    }


    void from_xml(const xml_node &node, ConnectionGeometry &obj)
    {
        log.ext_trace("Parsing ConnectionGeometry");
        


        log.ext_trace("Completed ConnectionGeometry");
    }


    void from_xml(const xml_node &node, SignalDictionary &obj)
    {
        log.ext_trace("Parsing SignalDictionary");
        


        log.ext_trace("Completed SignalDictionary");
    }


    void from_xml(const xml_node &node, TSignalDictionaries &obj)
    {
        log.ext_trace("Parsing TSignalDictionaries");
        
        ssp4cpp::common::xml::parse_xml(node, obj.SignalDictionaries  , "ssd:SignalDictionary");

        log.ext_trace("Completed TSignalDictionaries");
    }


    void from_xml(const xml_node &node, ParameterMapping &obj)
    {
        log.ext_trace("Parsing ParameterMapping");
        
        ssp4cpp::common::xml::parse_xml(node, obj.id                , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description       , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.type              , "type");
        ssp4cpp::common::xml::parse_xml(node, obj.source            , "source");
        ssp4cpp::common::xml::parse_xml(node, obj.sourceBase        , "sourceBase");
        ssp4cpp::common::xml::parse_xml(node, obj.ParameterMapping  , "ssm:ParameterMapping");

        log.ext_trace("Completed ParameterMapping");
    }


    void from_xml(const xml_node &node, ParameterBinding &obj)
    {
        log.ext_trace("Parsing ParameterBinding");
        
        ssp4cpp::common::xml::parse_xml(node, obj.id                , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description       , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.type              , "type");
        ssp4cpp::common::xml::parse_xml(node, obj.source            , "source");
        ssp4cpp::common::xml::parse_xml(node, obj.sourceBase        , "sourceBase");
        ssp4cpp::common::xml::parse_xml(node, obj.prefix            , "prefix");
        ssp4cpp::common::xml::parse_xml(node, obj.ParameterValues   , "ssv:ParameterValues");
        ssp4cpp::common::xml::parse_xml(node, obj.ParameterMapping  , "ssd:ParameterMapping");

        log.ext_trace("Completed ParameterBinding");
    }


    void from_xml(const xml_node &node, TParameterBindings &obj)
    {
        log.ext_trace("Parsing TParameterBindings");
        
        ssp4cpp::common::xml::parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBinding");

        log.ext_trace("Completed TParameterBindings");
    }


    void from_xml(const xml_node &node, GraphicalElements &obj)
    {
        log.ext_trace("Parsing GraphicalElements");
        


        log.ext_trace("Completed GraphicalElements");
    }


    void from_xml(const xml_node &node, TDefaultExperiment &obj)
    {
        log.ext_trace("Parsing TDefaultExperiment");
        
        ssp4cpp::common::xml::parse_xml(node, obj.startTime    , "startTime");
        ssp4cpp::common::xml::parse_xml(node, obj.stopTime     , "stopTime");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        log.ext_trace("Completed TDefaultExperiment");
    }


    void from_xml(const xml_node &node, Connection &obj)
    {
        log.ext_trace("Parsing Connection");
        
        ssp4cpp::common::xml::parse_xml(node, obj.id                                , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description                       , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.startElement                      , "startElement");
        ssp4cpp::common::xml::parse_xml(node, obj.startConnector                    , "startConnector");
        ssp4cpp::common::xml::parse_xml(node, obj.endElement                        , "endElement");
        ssp4cpp::common::xml::parse_xml(node, obj.endConnector                      , "endConnector");
        ssp4cpp::common::xml::parse_xml(node, obj.suppressUnitConversion            , "suppressUnitConversion");
        ssp4cpp::common::xml::parse_xml(node, obj.LinearTransformation              , "ssc:LinearTransformation");
        ssp4cpp::common::xml::parse_xml(node, obj.BooleanMappingTransformation      , "ssc:BooleanMappingTransformation");
        ssp4cpp::common::xml::parse_xml(node, obj.IntegerMappingTransformation      , "ssc:IntegerMappingTransformation");
        ssp4cpp::common::xml::parse_xml(node, obj.EnumerationMappingTransformation  , "ssc:EnumerationMappingTransformation");
        ssp4cpp::common::xml::parse_xml(node, obj.ConnectionGeometry                , "ssd:ConnectionGeometry");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations                       , "ssc:Annotations");

        log.ext_trace("Completed Connection");
    }


    void from_xml(const xml_node &node, Connections &obj)
    {
        log.ext_trace("Parsing Connections");
        
        ssp4cpp::common::xml::parse_xml(node, obj.Connections  , "ssd:Connection");

        log.ext_trace("Completed Connections");
    }


    void from_xml(const xml_node &node, Connector &obj)
    {
        log.ext_trace("Parsing Connector");
        
        ssp4cpp::common::xml::parse_xml(node, obj.id                 , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description        , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.name               , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.kind               , "kind");
        ssp4cpp::common::xml::parse_xml(node, obj.Real               , "ssc:Real");
        ssp4cpp::common::xml::parse_xml(node, obj.Integer            , "ssc:Integer");
        ssp4cpp::common::xml::parse_xml(node, obj.Boolean            , "ssc:Boolean");
        ssp4cpp::common::xml::parse_xml(node, obj.String             , "ssc:String");
        ssp4cpp::common::xml::parse_xml(node, obj.Enumeration        , "ssc:Enumeration");
        ssp4cpp::common::xml::parse_xml(node, obj.Binary             , "ssc:Binary");
        ssp4cpp::common::xml::parse_xml(node, obj.ConnectorGeometry  , "ssd:ConnectorGeometry");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations        , "ssc:Annotations");

        log.ext_trace("Completed Connector");
    }


    void from_xml(const xml_node &node, TConnectors &obj)
    {
        log.ext_trace("Parsing TConnectors");
        
        ssp4cpp::common::xml::parse_xml(node, obj.Connectors  , "ssd:Connector");

        log.ext_trace("Completed TConnectors");
    }


    void from_xml(const xml_node &node, TComponent &obj)
    {
        log.ext_trace("Parsing TComponent");
        
        ssp4cpp::common::xml::parse_xml(node, obj.id                 , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description        , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.name               , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.Connectors         , "ssd:Connectors");
        ssp4cpp::common::xml::parse_xml(node, obj.ElementGeometry    , "ssd:ElementGeometry");
        ssp4cpp::common::xml::parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBindings");
        ssp4cpp::common::xml::parse_xml(node, obj.type               , "type");
        ssp4cpp::common::xml::parse_xml(node, obj.source             , "source");
        ssp4cpp::common::xml::parse_xml(node, obj.implementation     , "implementation");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations        , "ssc:Annotations");

        log.ext_trace("Completed TComponent");
    }


    void from_xml(const xml_node &node, TSignalDictionaryReference &obj)
    {
        log.ext_trace("Parsing TSignalDictionaryReference");
        
        ssp4cpp::common::xml::parse_xml(node, obj.id                 , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description        , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.name               , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.Connectors         , "ssd:Connectors");
        ssp4cpp::common::xml::parse_xml(node, obj.ElementGeometry    , "ssd:ElementGeometry");
        ssp4cpp::common::xml::parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBindings");
        ssp4cpp::common::xml::parse_xml(node, obj.dictionary         , "dictionary");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations        , "ssc:Annotations");

        log.ext_trace("Completed TSignalDictionaryReference");
    }


    void from_xml(const xml_node &node, Elements &obj)
    {
        log.ext_trace("Parsing Elements");
        
        ssp4cpp::common::xml::parse_xml(node, obj.Components                  , "ssd:Component");
        ssp4cpp::common::xml::parse_xml(node, obj.SignalDictionaryReferences  , "ssd:SignalDictionaryReference");
        ssp4cpp::common::xml::parse_xml(node, obj.Systems                     , "ssd:System");

        log.ext_trace("Completed Elements");
    }


    void from_xml(const xml_node &node, TSystem &obj)
    {
        log.ext_trace("Parsing TSystem");
        
        ssp4cpp::common::xml::parse_xml(node, obj.id                  , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description         , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.name                , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.Connectors          , "ssd:Connectors");
        ssp4cpp::common::xml::parse_xml(node, obj.ElementGeometry     , "ssd:ElementGeometry");
        ssp4cpp::common::xml::parse_xml(node, obj.ParameterBindings   , "ssd:ParameterBindings");
        ssp4cpp::common::xml::parse_xml(node, obj.Elements            , "ssd:Elements");
        ssp4cpp::common::xml::parse_xml(node, obj.Connections         , "ssd:Connections");
        ssp4cpp::common::xml::parse_xml(node, obj.SignalDictionaries  , "ssd:SignalDictionaries");
        ssp4cpp::common::xml::parse_xml(node, obj.SystemGeometry      , "ssd:SystemGeometry");
        ssp4cpp::common::xml::parse_xml(node, obj.GraphicalElements   , "ssd:GraphicalElements");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations         , "ssc:Annotations");

        log.ext_trace("Completed TSystem");
    }


    void from_xml(const xml_node &node, SystemStructureDescription &obj)
    {
        log.ext_trace("Parsing SystemStructureDescription");
        
        ssp4cpp::common::xml::parse_xml(node, obj.version                , "version");
        ssp4cpp::common::xml::parse_xml(node, obj.name                   , "name");
        ssp4cpp::common::xml::parse_xml(node, obj.id                     , "id");
        ssp4cpp::common::xml::parse_xml(node, obj.description            , "description");
        ssp4cpp::common::xml::parse_xml(node, obj.author                 , "author");
        ssp4cpp::common::xml::parse_xml(node, obj.fileversion            , "fileversion");
        ssp4cpp::common::xml::parse_xml(node, obj.copyright              , "copyright");
        ssp4cpp::common::xml::parse_xml(node, obj.license                , "license");
        ssp4cpp::common::xml::parse_xml(node, obj.generationTool         , "generationTool");
        ssp4cpp::common::xml::parse_xml(node, obj.generationDateAndTime  , "generationDateAndTime");
        ssp4cpp::common::xml::parse_xml(node, obj.System                 , "ssd:System");
        ssp4cpp::common::xml::parse_xml(node, obj.Enumerations           , "ssc:Enumerations");
        ssp4cpp::common::xml::parse_xml(node, obj.Units                  , "ssc:Units");
        ssp4cpp::common::xml::parse_xml(node, obj.DefaultExperiment      , "ssd:DefaultExperiment");
        ssp4cpp::common::xml::parse_xml(node, obj.Annotations            , "ssc:Annotations");

        log.ext_trace("Completed SystemStructureDescription");
    }

}
