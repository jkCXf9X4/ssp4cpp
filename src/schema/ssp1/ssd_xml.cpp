#include <boost/log/trivial.hpp>

#include "SystemStructureDescription.hpp"

#include "ssc_xml.hpp"
#include "ssd_xml.hpp"

#include "xml_deserialize.hpp"


namespace ssp4cpp::ssp1::ssd
{
    using namespace std;
    using namespace pugi;
    using namespace ssp4cpp::xml;

    void from_xml(const xml_node &node, ElementGeometry &geometry) {}

    void from_xml(const xml_node &node, TDefaultExperiment &experiment) {}

    void from_xml(const xml_node &node, TParameterBindings &bindings) {}

    void from_xml(const xml_node &node, TSignalDictionaries &dictionaries) {}

    void from_xml(const xml_node &node, SystemGeometry &geometry) {}

    void from_xml(const xml_node &node, GraphicalElements &elements) {}

    void from_xml(const xml_node &node, ConnectorGeometry &geometry) {}

    void from_xml(const xml_node &node, ConnectionGeometry &geometry) {}

    void from_xml(const xml_node &node, Connections &connections)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connections" << std::endl;

        get_vector(node, "ssd:Connection", connections.list);

        BOOST_LOG_TRIVIAL(trace) << "Completed Connections" << std::endl;
    }

    void from_xml(const xml_node &node, Connection &connection)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connection" << std::endl;

        connection.startElement = get_optional_attribute<string>(node, "startElement");
        connection.startConnector = get_attribute<string>(node, "startConnector");
        connection.endElement = get_optional_attribute<string>(node, "endElement");
        connection.endConnector = get_attribute<string>(node, "endConnector");
        connection.suppressUnitConversion = get_optional_attribute<bool>(node, "suppressUnitConversion");
        get_optional_class(node, "ssc:LinearTransformation", connection.LinearTransformation);
        get_optional_class(node, "ssc:BooleanMappingTransformation", connection.BooleanMappingTransformation);
        get_optional_class(node, "ssc:IntegerMappingTransformation", connection.IntegerMappingTransformation);
        get_optional_class(node, "ssc:EnumerationMappingTransformation", connection.EnumerationMappingTransformation);
        get_optional_class(node, "ssd:ConnectionGeometry", connection.ConnectionGeometry);
        get_optional_class(node, "ssc:Annotations", connection.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed Connection" << std::endl;
    }

    void from_xml(const xml_node &node, TConnectors &connectors)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TConnectors" << std::endl;

        get_vector(node, "ssd:Connector", connectors.list);

        BOOST_LOG_TRIVIAL(trace) << "Completed TConnectors" << std::endl;
    }

    void from_xml(const xml_node &node, Connector &conn)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Connector" << std::endl;

        conn.description = get_optional_attribute<string>(node, "description");
        conn.id = get_optional_attribute<string>(node, "id");

        conn.name = get_attribute<string>(node, "name");
        conn.kind = get_attribute<string>(node, "kind");
        get_optional_class(node, "ssc:Real", conn.Real);
        get_optional_class(node, "ssc:Integer", conn.Integer);
        get_optional_class(node, "ssc:Boolean", conn.Boolean);
        get_optional_class(node, "ssc:String", conn.String);
        get_optional_class(node, "ssc:Enumeration", conn.Enumeration);
        get_optional_class(node, "ssc:Binary", conn.Binary);

        get_optional_class(node, "ssd:ConnectorGeometry", conn.ConnectorGeometry);
        get_optional_class(node, "ssc:Annotations", conn.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed Connector" << std::endl;
    }

    void from_xml(const xml_node &node, TComponent &comp)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TComponent" << std::endl;

        comp.description = get_optional_attribute<string>(node, "description");
        comp.id = get_optional_attribute<string>(node, "id");

        comp.name = get_optional_attribute<string>(node, "name");
        get_optional_class(node, "ssd:Connectors", comp.Connectors);
        get_optional_class(node, "ssd:ElementGeometry", comp.ElementGeometry);
        get_optional_class(node, "ssd:ParameterBindings", comp.TParameterBindings);

        comp.component_type = get_optional_attribute<string>(node, "type");
        comp.source = get_attribute<string>(node, "source");
        comp.implementation = get_optional_attribute<string>(node, "implementation");
        get_optional_class(node, "ssc:Annotations", comp.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed TComponent: " << std::endl;
    }

    void from_xml(const xml_node &node, TSignalDictionaryReference &ref)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TSignalDictionaryReference" << std::endl;

        ref.dictionary = get_attribute<string>(node, "dictionary");
        get_optional_class(node, "ssd:Connectors", ref.Connectors);
        get_optional_class(node, "ssd:ElementGeometry", ref.ElementGeometry);
        get_optional_class(node, "ssd:ParameterBindings", ref.TParameterBindings);
        get_optional_class(node, "ssc:Annotations", ref.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed TSignalDictionaryReference" << std::endl;
    }

    void from_xml(const xml_node &node, Elements &elements)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing Elements" << std::endl;

        get_vector(node, "ssd:Component", elements.components);
        get_vector(node, "ssd:SignalDictionaryReference", elements.signal_dictionary_references);
        get_vector(node, "ssd:System", elements.systems);

        BOOST_LOG_TRIVIAL(trace) << "Completed Elements" << std::endl;
    }

    void from_xml(const xml_node &node, TSystem &sys)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing TSystem" << std::endl;

        sys.id = get_optional_attribute<string>(node, "id");
        sys.description = get_optional_attribute<string>(node, "description");

        sys.name = get_optional_attribute<string>(node, "name");
        get_optional_class(node, "ssd:Connectors", sys.Connectors);
        get_optional_class(node, "ssd:ElementGeometry", sys.ElementGeometry);
        get_optional_class(node, "ssd:ParameterBindings", sys.ParameterBindings);

        get_optional_class(node, "ssd:Elements", sys.Elements);
        get_optional_class(node, "ssd:Connections", sys.Connections);
        get_optional_class(node, "ssd:SignalDictionaries", sys.SignalDictionaries);
        get_optional_class(node, "ssd:SystemGeometry", sys.SystemGeometry);
        get_optional_class(node, "ssd:GraphicalElements", sys.GraphicalElements);
        get_optional_class(node, "ssc:Annotations", sys.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed TSystem" << std::endl;
    }

    void from_xml(const xml_node &node, SystemStructureDescription &desc)
    {
        BOOST_LOG_TRIVIAL(trace) << "Parsing SystemStructureDescription" << std::endl;

        desc.version = get_attribute<string>(node, "version");
        desc.name = get_attribute<string>(node, "name");

        desc.id = get_optional_attribute<string>(node, "id");
        desc.description = get_optional_attribute<string>(node, "description");
        desc.author = get_optional_attribute<string>(node, "author");
        desc.fileversion = get_optional_attribute<string>(node, "fileversion");
        desc.copyright = get_optional_attribute<string>(node, "copyright");
        desc.license = get_optional_attribute<string>(node, "license");
        desc.generationTool = get_optional_attribute<string>(node, "generationTool");
        desc.generationDateAndTime = get_optional_attribute<string>(node, "generationDateAndTime");

        from_xml(node.child("ssd:System"), desc.System);

        get_optional_class(node, "ssc:Enumerations", desc.Enumerations);
        get_optional_class(node, "ssc:TUnits", desc.Units);
        get_optional_class(node, "ssd:DefaultExperiment", desc.DefaultExperiment);
        get_optional_class(node, "ssc:Annotations", desc.Annotations);

        BOOST_LOG_TRIVIAL(trace) << "Completed SystemStructureDescription" << std::endl;
    }
}