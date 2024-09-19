{
    class SystemGeometry
    {
    public:

    };
    string to_string(const SystemGeometry &obj);
    string to_string(const optional<SystemGeometry> &obj);
    string to_string(const vector<SystemGeometry> &obj);

    class ConnectorGeometry
    {
    public:

    };
    string to_string(const ConnectorGeometry &obj);
    string to_string(const optional<ConnectorGeometry> &obj);
    string to_string(const vector<ConnectorGeometry> &obj);

    class ElementGeometry
    {
    public:

    };
    string to_string(const ElementGeometry &obj);
    string to_string(const optional<ElementGeometry> &obj);
    string to_string(const vector<ElementGeometry> &obj);

    class ConnectionGeometry
    {
    public:

    };
    string to_string(const ConnectionGeometry &obj);
    string to_string(const optional<ConnectionGeometry> &obj);
    string to_string(const vector<ConnectionGeometry> &obj);

    class TSignalDictionaries
    {
    public:

    };
    string to_string(const TSignalDictionaries &obj);
    string to_string(const optional<TSignalDictionaries> &obj);
    string to_string(const vector<TSignalDictionaries> &obj);

    class TParameterBindings
    {
    public:

    };
    string to_string(const TParameterBindings &obj);
    string to_string(const optional<TParameterBindings> &obj);
    string to_string(const vector<TParameterBindings> &obj);

    class GraphicalElements
    {
    public:

    };
    string to_string(const GraphicalElements &obj);
    string to_string(const optional<GraphicalElements> &obj);
    string to_string(const vector<GraphicalElements> &obj);

    class TDefaultExperiment
    {
    public:

    };
    string to_string(const TDefaultExperiment &obj);
    string to_string(const optional<TDefaultExperiment> &obj);
    string to_string(const vector<TDefaultExperiment> &obj);

    class Connection
    {
    public:
        optional<string> startElement;
        string startConnector;
        optional<string> endElement;
        string endConnector;
        optional<bool> suppressUnitConversion;
        optional<ssc::LinearTransformation> LinearTransformation;
        optional<ssc::BooleanMappingTransformation> BooleanMappingTransformation;
        optional<ssc::IntegerMappingTransformation> IntegerMappingTransformation;
        optional<ssc::EnumerationMappingTransformation> EnumerationMappingTransformation;
        optional<ssd::ConnectionGeometry> ConnectionGeometry;
        optional<ssc::TAnnotations> Annotations;
    };
    string to_string(const Connection &obj);
    string to_string(const optional<Connection> &obj);
    string to_string(const vector<Connection> &obj);

    class Connections
    {
    public:
        vector<Connection> list;
    };
    string to_string(const Connections &obj);
    string to_string(const optional<Connections> &obj);
    string to_string(const vector<Connections> &obj);

    class Connector
    {
    public:
        optional<string> id;
        optional<string> description;
        string name;
        string kind;
        optional<ssc::GTypeReal> Real;
        optional<ssc::GTypeInteger> Integer;
        optional<ssc::GTypeBoolean> Boolean;
        optional<ssc::GTypeString> String;
        optional<ssc::GTypeEnumeration> Enumeration;
        optional<ssc::GTypeBinary> Binary;
        optional<ssd::ConnectorGeometry> ConnectorGeometry;
        optional<ssc::TAnnotations> Annotations;
    };
    string to_string(const Connector &obj);
    string to_string(const optional<Connector> &obj);
    string to_string(const vector<Connector> &obj);

    class TConnectors
    {
    public:
        vector<Connector> list;
    };
    string to_string(const TConnectors &obj);
    string to_string(const optional<TConnectors> &obj);
    string to_string(const vector<TConnectors> &obj);

    class TComponent
    {
    public:
        optional<string> id;
        optional<string> description;
        optional<string> name;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> TParameterBindings;
        optional<string> component_type_str;
        optional<ComponentType> component_type;
        string source;
        optional<string> implementation;
        optional<ssc::TAnnotations> Annotations;
    };
    string to_string(const TComponent &obj);
    string to_string(const optional<TComponent> &obj);
    string to_string(const vector<TComponent> &obj);

    class TSignalDictionaryReference
    {
    public:
        string dictionary;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> TParameterBindings;
        optional<ssc::TAnnotations> Annotations;
    };
    string to_string(const TSignalDictionaryReference &obj);
    string to_string(const optional<TSignalDictionaryReference> &obj);
    string to_string(const vector<TSignalDictionaryReference> &obj);

    class Elements
    {
    public:
        vector<ssd::TComponent> components;
        vector<ssd::TSignalDictionaryReference> signal_dictionary_references;
        vector<ssd::TSystem> systems;
    };
    string to_string(const Elements &obj);
    string to_string(const optional<Elements> &obj);
    string to_string(const vector<Elements> &obj);

    class TSystem
    {
    public:
        optional<string> id;
        optional<string> description;
        optional<string> name;
        optional<ssd::TConnectors> Connectors;
        optional<ssd::ElementGeometry> ElementGeometry;
        optional<ssd::TParameterBindings> ParameterBindings;
        optional<ssd::Elements> Elements;
        optional<ssd::Connections> Connections;
        optional<ssd::TSignalDictionaries> SignalDictionaries;
        optional<ssd::SystemGeometry> SystemGeometry;
        optional<ssd::GraphicalElements> GraphicalElements;
        optional<ssc::TAnnotations> Annotations;
    };
    string to_string(const TSystem &obj);
    string to_string(const optional<TSystem> &obj);
    string to_string(const vector<TSystem> &obj);

    class SystemStructureDescription
    {
    public:
        string version;
        string name;
        optional<string> id;
        optional<string> description;
        optional<string> author;
        optional<string> fileversion;
        optional<string> copyright;
        optional<string> license;
        optional<string> generationTool;
        optional<string> generationDateAndTime;
        ssd::TSystem System;
        optional<ssc::TEnumerations> Enumerations;
        optional<ssc::TUnits> Units;
        optional<ssd::TDefaultExperiment> DefaultExperiment;
        optional<ssc::TAnnotations> Annotations;
    };
    string to_string(const SystemStructureDescription &obj);
    string to_string(const optional<SystemStructureDescription> &obj);
    string to_string(const vector<SystemStructureDescription> &obj);
}