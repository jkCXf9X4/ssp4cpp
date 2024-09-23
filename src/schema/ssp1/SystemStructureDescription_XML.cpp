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

    void from_xml(const xml_node &node, TSignalDictionaries &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TSignalDictionaries" << std::endl;



        BOOST_LOG_TRIVIAL(trace) << "Completed TSignalDictionaries" << std::endl;
    }

    void from_xml(const xml_node &node, TParameterBindings &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TParameterBindings" << std::endl;



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



        BOOST_LOG_TRIVIAL(trace) << "Completed TDefaultExperiment" << std::endl;
    }

    void from_xml(const xml_node &node, Connection &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connection" << std::endl;

        obj.startElement = get_optional_attribute<string>(node, "startElement");
        obj.startConnector = get_attribute<string>(node, "startConnector");
        obj.endElement = get_optional_attribute<string>(node, "endElement");
        obj.endConnector = get_attribute<string>(node, "endConnector");
        obj.suppressUnitConversion = get_optional_attribute<bool>(node, "suppressUnitConversion");
        get_optional_class(node, "ssc:LinearTransformation", obj.LinearTransformation);
        get_optional_class(node, "ssc:BooleanMappingTransformation", obj.BooleanMappingTransformation);
        get_optional_class(node, "ssc:IntegerMappingTransformation", obj.IntegerMappingTransformation);
        get_optional_class(node, "ssc:EnumerationMappingTransformation", obj.EnumerationMappingTransformation);
        get_optional_class(node, "ssd:ConnectionGeometry", obj.ConnectionGeometry);
        get_optional_class(node, "ssc:Annotations", obj.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed Connection" << std::endl;
    }

    void from_xml(const xml_node &node, Connections &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connections" << std::endl;

        get_vector(node, "ssd:Connection", obj.Connection);

        BOOST_LOG_TRIVIAL(trace) << "Completed Connections" << std::endl;
    }

    void from_xml(const xml_node &node, Connector &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connector" << std::endl;

        obj.id = get_optional_attribute<string>(node, "id");
        obj.description = get_optional_attribute<string>(node, "description");
        obj.name = get_attribute<string>(node, "name");
        obj.kind = get_attribute<string>(node, "kind");
        get_optional_class(node, "ssc:Real", obj.Real);
        get_optional_class(node, "ssc:Integer", obj.Integer);
        get_optional_class(node, "ssc:Boolean", obj.Boolean);
        get_optional_class(node, "ssc:String", obj.String);
        get_optional_class(node, "ssc:Enumeration", obj.Enumeration);
        get_optional_class(node, "ssc:Binary", obj.Binary);
        get_optional_class(node, "ssd:ConnectorGeometry", obj.ConnectorGeometry);
        get_optional_class(node, "ssc:Annotations", obj.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed Connector" << std::endl;
    }

    void from_xml(const xml_node &node, TConnectors &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TConnectors" << std::endl;

        get_vector(node, "ssd:Connector", obj.Connector);

        BOOST_LOG_TRIVIAL(trace) << "Completed TConnectors" << std::endl;
    }

    void from_xml(const xml_node &node, TComponent &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TComponent" << std::endl;

        obj.id = get_optional_attribute<string>(node, "id");
        obj.description = get_optional_attribute<string>(node, "description");
        obj.name = get_optional_attribute<string>(node, "name");
        get_optional_class(node, "ssd:Connectors", obj.Connectors);
        get_optional_class(node, "ssd:ElementGeometry", obj.ElementGeometry);
        get_optional_class(node, "ssd:ParameterBindings", obj.ParameterBindings);
        obj.type = get_optional_attribute<string>(node, "type");
        obj.source = get_attribute<string>(node, "source");
        obj.implementation = get_optional_attribute<string>(node, "implementation");
        get_optional_class(node, "ssc:Annotations", obj.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed TComponent" << std::endl;
    }

    void from_xml(const xml_node &node, TSignalDictionaryReference &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TSignalDictionaryReference" << std::endl;

        obj.dictionary = get_attribute<string>(node, "dictionary");
        get_optional_class(node, "ssd:Connectors", obj.Connectors);
        get_optional_class(node, "ssd:ElementGeometry", obj.ElementGeometry);
        get_optional_class(node, "ssd:ParameterBindings", obj.ParameterBindings);
        get_optional_class(node, "ssc:Annotations", obj.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed TSignalDictionaryReference" << std::endl;
    }

    void from_xml(const xml_node &node, Elements &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Elements" << std::endl;

        get_vector(node, "ssd:Component", obj.Component);
        get_vector(node, "ssd:SignalDictionaryReference", obj.SignalDictionaryReference);
        get_vector(node, "ssd:System", obj.System);

        BOOST_LOG_TRIVIAL(trace) << "Completed Elements" << std::endl;
    }

    void from_xml(const xml_node &node, TSystem &obj)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TSystem" << std::endl;

        obj.id = get_optional_attribute<string>(node, "id");
        obj.description = get_optional_attribute<string>(node, "description");
        obj.name = get_optional_attribute<string>(node, "name");
        get_optional_class(node, "ssd:Connectors", obj.Connectors);
        get_optional_class(node, "ssd:ElementGeometry", obj.ElementGeometry);
        get_optional_class(node, "ssd:ParameterBindings", obj.ParameterBindings);
        get_optional_class(node, "ssd:Elements", obj.Elements);
        get_optional_class(node, "ssd:Connections", obj.Connections);
        get_optional_class(node, "ssd:SignalDictionaries", obj.SignalDictionaries);
        get_optional_class(node, "ssd:SystemGeometry", obj.SystemGeometry);
        get_optional_class(node, "ssd:GraphicalElements", obj.GraphicalElements);
        get_optional_class(node, "ssc:Annotations", obj.Annotations);

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
