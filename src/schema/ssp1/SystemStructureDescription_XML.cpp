#include <boost/log/trivial.hpp>

#include "SystemStructureDescription.hpp"

#include "SystemStructureCommon_XML.hpp"
#include "SystemStructureDescription_XML.hpp"

#include "xml_deserialize.hpp"

    using namespace std;
    using namespace pugi;
    using namespace ssp4cpp::xml;
    
namespace ssp4cpp::ssp1::ssd
{

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

        parse_xml(node, obj.SignalDictionaries  , "ssd:SignalDictionary");

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

        parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBinding");

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

        parse_xml(node, obj.startTime    , "startTime");
        parse_xml(node, obj.stopTime     , "stopTime");
        parse_xml(node, obj.Annotations  , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed TDefaultExperiment" << std::endl;
    }

    void from_xml(const xml_node &node, Connection &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connection" << std::endl;

        parse_xml(node, obj.id                                , "id");
        parse_xml(node, obj.description                       , "description");
        parse_xml(node, obj.startElement                      , "startElement");
        parse_xml(node, obj.startConnector                    , "startConnector");
        parse_xml(node, obj.endElement                        , "endElement");
        parse_xml(node, obj.endConnector                      , "endConnector");
        parse_xml(node, obj.suppressUnitConversion            , "suppressUnitConversion");
        parse_xml(node, obj.LinearTransformation              , "ssc:LinearTransformation");
        parse_xml(node, obj.BooleanMappingTransformation      , "ssc:BooleanMappingTransformation");
        parse_xml(node, obj.IntegerMappingTransformation      , "ssc:IntegerMappingTransformation");
        parse_xml(node, obj.EnumerationMappingTransformation  , "ssc:EnumerationMappingTransformation");
        parse_xml(node, obj.ConnectionGeometry                , "ssd:ConnectionGeometry");
        parse_xml(node, obj.Annotations                       , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed Connection" << std::endl;
    }

    void from_xml(const xml_node &node, Connections &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connections" << std::endl;

        parse_xml(node, obj.Connections  , "ssd:Connection");

        BOOST_LOG_TRIVIAL(trace) << "Completed Connections" << std::endl;
    }

    void from_xml(const xml_node &node, Connector &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connector" << std::endl;

        parse_xml(node, obj.id                 , "id");
        parse_xml(node, obj.description        , "description");
        parse_xml(node, obj.name               , "name");
        parse_xml(node, obj.kind               , "kind");
        parse_xml(node, obj.Real               , "ssc:Real");
        parse_xml(node, obj.Integer            , "ssc:Integer");
        parse_xml(node, obj.Boolean            , "ssc:Boolean");
        parse_xml(node, obj.String             , "ssc:String");
        parse_xml(node, obj.Enumeration        , "ssc:Enumeration");
        parse_xml(node, obj.Binary             , "ssc:Binary");
        parse_xml(node, obj.ConnectorGeometry  , "ssd:ConnectorGeometry");
        parse_xml(node, obj.Annotations        , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed Connector" << std::endl;
    }

    void from_xml(const xml_node &node, TConnectors &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TConnectors" << std::endl;

        parse_xml(node, obj.Connectors  , "ssd:Connector");

        BOOST_LOG_TRIVIAL(trace) << "Completed TConnectors" << std::endl;
    }

    void from_xml(const xml_node &node, TComponent &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TComponent" << std::endl;

        parse_xml(node, obj.id                 , "id");
        parse_xml(node, obj.description        , "description");
        parse_xml(node, obj.name               , "name");
        parse_xml(node, obj.Connectors         , "ssd:Connectors");
        parse_xml(node, obj.ElementGeometry    , "ssd:ElementGeometry");
        parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBindings");
        parse_xml(node, obj.type               , "type");
        parse_xml(node, obj.source             , "source");
        parse_xml(node, obj.implementation     , "implementation");
        parse_xml(node, obj.Annotations        , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed TComponent" << std::endl;
    }

    void from_xml(const xml_node &node, TSignalDictionaryReference &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TSignalDictionaryReference" << std::endl;

        parse_xml(node, obj.id                 , "id");
        parse_xml(node, obj.description        , "description");
        parse_xml(node, obj.name               , "name");
        parse_xml(node, obj.Connectors         , "ssd:Connectors");
        parse_xml(node, obj.ElementGeometry    , "ssd:ElementGeometry");
        parse_xml(node, obj.ParameterBindings  , "ssd:ParameterBindings");
        parse_xml(node, obj.dictionary         , "dictionary");
        parse_xml(node, obj.Annotations        , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed TSignalDictionaryReference" << std::endl;
    }

    void from_xml(const xml_node &node, Elements &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Elements" << std::endl;

        parse_xml(node, obj.Components                  , "ssd:Component");
        parse_xml(node, obj.SignalDictionaryReferences  , "ssd:SignalDictionaryReference");
        parse_xml(node, obj.Systems                     , "ssd:System");

        BOOST_LOG_TRIVIAL(trace) << "Completed Elements" << std::endl;
    }

    void from_xml(const xml_node &node, TSystem &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TSystem" << std::endl;

        parse_xml(node, obj.id                  , "id");
        parse_xml(node, obj.description         , "description");
        parse_xml(node, obj.name                , "name");
        parse_xml(node, obj.Connectors          , "ssd:Connectors");
        parse_xml(node, obj.ElementGeometry     , "ssd:ElementGeometry");
        parse_xml(node, obj.ParameterBindings   , "ssd:ParameterBindings");
        parse_xml(node, obj.Elements            , "ssd:Elements");
        parse_xml(node, obj.Connections         , "ssd:Connections");
        parse_xml(node, obj.SignalDictionaries  , "ssd:SignalDictionaries");
        parse_xml(node, obj.SystemGeometry      , "ssd:SystemGeometry");
        parse_xml(node, obj.GraphicalElements   , "ssd:GraphicalElements");
        parse_xml(node, obj.Annotations         , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed TSystem" << std::endl;
    }

    void from_xml(const xml_node &node, SystemStructureDescription &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SystemStructureDescription" << std::endl;

        parse_xml(node, obj.version                , "version");
        parse_xml(node, obj.name                   , "name");
        parse_xml(node, obj.id                     , "id");
        parse_xml(node, obj.description            , "description");
        parse_xml(node, obj.author                 , "author");
        parse_xml(node, obj.fileversion            , "fileversion");
        parse_xml(node, obj.copyright              , "copyright");
        parse_xml(node, obj.license                , "license");
        parse_xml(node, obj.generationTool         , "generationTool");
        parse_xml(node, obj.generationDateAndTime  , "generationDateAndTime");
        parse_xml(node, obj.System                 , "ssd:System");
        parse_xml(node, obj.Enumerations           , "ssc:Enumerations");
        parse_xml(node, obj.Units                  , "ssc:Units");
        parse_xml(node, obj.DefaultExperiment      , "ssd:DefaultExperiment");
        parse_xml(node, obj.Annotations            , "ssc:Annotations");

        BOOST_LOG_TRIVIAL(trace) << "Completed SystemStructureDescription" << std::endl;
    }

}
