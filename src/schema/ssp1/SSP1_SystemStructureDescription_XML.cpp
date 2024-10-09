

// This is a generated file, do not alter
// it is based on ssp1_ssd.toml

#include "xml_deserialize.hpp"
#include "SSP1_SystemStructureDescription_XML.hpp"
#include "SSP1_SystemStructureCommon_XML.hpp"

using namespace std;
using namespace pugi;
using namespace ssp4cpp::xml;

#include <boost/log/trivial.hpp>

namespace ssp4cpp::ssp1::ssd
{
    using namespace pugi;


    void from_xml(const xml_node &node, SystemGeometry &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SystemGeometry" << std::endl;



        BOOST_LOG_TRIVIAL(trace) << "Completed SystemGeometry" << std::endl;
    }


    void from_xml(const xml_node &node, ConnectorGeometry &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ConnectorGeometry" << std::endl;



        BOOST_LOG_TRIVIAL(trace) << "Completed ConnectorGeometry" << std::endl;
    }


    void from_xml(const xml_node &node, ElementGeometry &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ElementGeometry" << std::endl;



        BOOST_LOG_TRIVIAL(trace) << "Completed ElementGeometry" << std::endl;
    }


    void from_xml(const xml_node &node, ConnectionGeometry &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ConnectionGeometry" << std::endl;



        BOOST_LOG_TRIVIAL(trace) << "Completed ConnectionGeometry" << std::endl;
    }


    void from_xml(const xml_node &node, SignalDictionary &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SignalDictionary" << std::endl;



        BOOST_LOG_TRIVIAL(trace) << "Completed SignalDictionary" << std::endl;
    }


    void from_xml(const xml_node &node, TSignalDictionaries &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TSignalDictionaries" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.SignalDictionaries  , "ssd:SignalDictionary");

        BOOST_LOG_TRIVIAL(trace) << "Completed TSignalDictionaries" << std::endl;
    }


    void from_xml(const xml_node &node, ParameterBinding &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing ParameterBinding" << std::endl;



        BOOST_LOG_TRIVIAL(trace) << "Completed ParameterBinding" << std::endl;
    }


    void from_xml(const xml_node &node, TParameterBindings &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TParameterBindings" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBinding");

        BOOST_LOG_TRIVIAL(trace) << "Completed TParameterBindings" << std::endl;
    }


    void from_xml(const xml_node &node, GraphicalElements &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing GraphicalElements" << std::endl;



        BOOST_LOG_TRIVIAL(trace) << "Completed GraphicalElements" << std::endl;
    }


    void from_xml(const xml_node &node, TDefaultExperiment &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TDefaultExperiment" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.startTime    , "startTime");
        ssp4cpp::xml::parse_xml(node, obj.stopTime     , "stopTime");
        ssp4cpp::xml::parse_xml(node, obj.Annotations  , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed TDefaultExperiment" << std::endl;
    }


    void from_xml(const xml_node &node, Connection &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connection" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.id                                , "id");
        ssp4cpp::xml::parse_xml(node, obj.description                       , "description");
        ssp4cpp::xml::parse_xml(node, obj.startElement                      , "startElement");
        ssp4cpp::xml::parse_xml(node, obj.startConnector                    , "startConnector");
        ssp4cpp::xml::parse_xml(node, obj.endElement                        , "endElement");
        ssp4cpp::xml::parse_xml(node, obj.endConnector                      , "endConnector");
        ssp4cpp::xml::parse_xml(node, obj.suppressUnitConversion            , "suppressUnitConversion");
        ssp4cpp::xml::parse_xml(node, obj.LinearTransformation              , "ssc:LinearTransformation");
        ssp4cpp::xml::parse_xml(node, obj.BooleanMappingTransformation      , "ssc:BooleanMappingTransformation");
        ssp4cpp::xml::parse_xml(node, obj.IntegerMappingTransformation      , "ssc:IntegerMappingTransformation");
        ssp4cpp::xml::parse_xml(node, obj.EnumerationMappingTransformation  , "ssc:EnumerationMappingTransformation");
        ssp4cpp::xml::parse_xml(node, obj.ConnectionGeometry                , "ssd:ConnectionGeometry");
        ssp4cpp::xml::parse_xml(node, obj.Annotations                       , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed Connection" << std::endl;
    }


    void from_xml(const xml_node &node, Connections &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connections" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Connections  , "ssd:Connection");

        BOOST_LOG_TRIVIAL(trace) << "Completed Connections" << std::endl;
    }


    void from_xml(const xml_node &node, Connector &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connector" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.id                 , "id");
        ssp4cpp::xml::parse_xml(node, obj.description        , "description");
        ssp4cpp::xml::parse_xml(node, obj.name               , "name");
        ssp4cpp::xml::parse_xml(node, obj.kind               , "kind");
        ssp4cpp::xml::parse_xml(node, obj.Real               , "ssc:Real");
        ssp4cpp::xml::parse_xml(node, obj.Integer            , "ssc:Integer");
        ssp4cpp::xml::parse_xml(node, obj.Boolean            , "ssc:Boolean");
        ssp4cpp::xml::parse_xml(node, obj.String             , "ssc:String");
        ssp4cpp::xml::parse_xml(node, obj.Enumeration        , "ssc:Enumeration");
        ssp4cpp::xml::parse_xml(node, obj.Binary             , "ssc:Binary");
        ssp4cpp::xml::parse_xml(node, obj.ConnectorGeometry  , "ssd:ConnectorGeometry");
        ssp4cpp::xml::parse_xml(node, obj.Annotations        , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed Connector" << std::endl;
    }


    void from_xml(const xml_node &node, TConnectors &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TConnectors" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Connectors  , "ssd:Connector");

        BOOST_LOG_TRIVIAL(trace) << "Completed TConnectors" << std::endl;
    }


    void from_xml(const xml_node &node, TComponent &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TComponent" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.id                 , "id");
        ssp4cpp::xml::parse_xml(node, obj.description        , "description");
        ssp4cpp::xml::parse_xml(node, obj.name               , "name");
        ssp4cpp::xml::parse_xml(node, obj.Connectors         , "ssd:Connectors");
        ssp4cpp::xml::parse_xml(node, obj.ElementGeometry    , "ssd:ElementGeometry");
        ssp4cpp::xml::parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBindings");
        ssp4cpp::xml::parse_xml(node, obj.type               , "type");
        ssp4cpp::xml::parse_xml(node, obj.source             , "source");
        ssp4cpp::xml::parse_xml(node, obj.implementation     , "implementation");
        ssp4cpp::xml::parse_xml(node, obj.Annotations        , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed TComponent" << std::endl;
    }


    void from_xml(const xml_node &node, TSignalDictionaryReference &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TSignalDictionaryReference" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.id                 , "id");
        ssp4cpp::xml::parse_xml(node, obj.description        , "description");
        ssp4cpp::xml::parse_xml(node, obj.name               , "name");
        ssp4cpp::xml::parse_xml(node, obj.Connectors         , "ssd:Connectors");
        ssp4cpp::xml::parse_xml(node, obj.ElementGeometry    , "ssd:ElementGeometry");
        ssp4cpp::xml::parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBindings");
        ssp4cpp::xml::parse_xml(node, obj.dictionary         , "dictionary");
        ssp4cpp::xml::parse_xml(node, obj.Annotations        , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed TSignalDictionaryReference" << std::endl;
    }


    void from_xml(const xml_node &node, Elements &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Elements" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.Components                  , "ssd:Component");
        ssp4cpp::xml::parse_xml(node, obj.SignalDictionaryReferences  , "ssd:SignalDictionaryReference");
        ssp4cpp::xml::parse_xml(node, obj.Systems                     , "ssd:System");

        BOOST_LOG_TRIVIAL(trace) << "Completed Elements" << std::endl;
    }


    void from_xml(const xml_node &node, TSystem &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TSystem" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.id                  , "id");
        ssp4cpp::xml::parse_xml(node, obj.description         , "description");
        ssp4cpp::xml::parse_xml(node, obj.name                , "name");
        ssp4cpp::xml::parse_xml(node, obj.Connectors          , "ssd:Connectors");
        ssp4cpp::xml::parse_xml(node, obj.ElementGeometry     , "ssd:ElementGeometry");
        ssp4cpp::xml::parse_xml(node, obj.ParameterBindings   , "ssd:ParameterBindings");
        ssp4cpp::xml::parse_xml(node, obj.Elements            , "ssd:Elements");
        ssp4cpp::xml::parse_xml(node, obj.Connections         , "ssd:Connections");
        ssp4cpp::xml::parse_xml(node, obj.SignalDictionaries  , "ssd:SignalDictionaries");
        ssp4cpp::xml::parse_xml(node, obj.SystemGeometry      , "ssd:SystemGeometry");
        ssp4cpp::xml::parse_xml(node, obj.GraphicalElements   , "ssd:GraphicalElements");
        ssp4cpp::xml::parse_xml(node, obj.Annotations         , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed TSystem" << std::endl;
    }


    void from_xml(const xml_node &node, SystemStructureDescription &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SystemStructureDescription" << std::endl;

        ssp4cpp::xml::parse_xml(node, obj.version                , "version");
        ssp4cpp::xml::parse_xml(node, obj.name                   , "name");
        ssp4cpp::xml::parse_xml(node, obj.id                     , "id");
        ssp4cpp::xml::parse_xml(node, obj.description            , "description");
        ssp4cpp::xml::parse_xml(node, obj.author                 , "author");
        ssp4cpp::xml::parse_xml(node, obj.fileversion            , "fileversion");
        ssp4cpp::xml::parse_xml(node, obj.copyright              , "copyright");
        ssp4cpp::xml::parse_xml(node, obj.license                , "license");
        ssp4cpp::xml::parse_xml(node, obj.generationTool         , "generationTool");
        ssp4cpp::xml::parse_xml(node, obj.generationDateAndTime  , "generationDateAndTime");
        ssp4cpp::xml::parse_xml(node, obj.System                 , "ssd:System");
        ssp4cpp::xml::parse_xml(node, obj.Enumerations           , "ssc:Enumerations");
        ssp4cpp::xml::parse_xml(node, obj.Units                  , "ssc:Units");
        ssp4cpp::xml::parse_xml(node, obj.DefaultExperiment      , "ssd:DefaultExperiment");
        ssp4cpp::xml::parse_xml(node, obj.Annotations            , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed SystemStructureDescription" << std::endl;
    }

}
