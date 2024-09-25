{

    class BaseUnit : public IXmlNode
    {
    public:
        optional<int> kg;
        optional<int> m;
        optional<int> s;
        optional<int> a;
        optional<int> k;
        optional<int> mol;
        optional<int> cd;
        optional<int> rad;
        optional<double> factor;
        optional<double> offset;

        string to_string(void) const;


    };


    class DisplayUnit : public IXmlNode
    {
    public:
        string name;
        optional<double> factor;
        optional<double> offset;

        string to_string(void) const;


    };


    class fmi2Unit : public IXmlNode
    {
    public:
        string name;
        optional<fmi2::BaseUnit> BaseUnit;
        vector<fmi2::DisplayUnit> DisplayUnit;

        string to_string(void) const;


    };


    class UnitDefinitions : public IXmlNode
    {
    public:
        vector<fmi2::fmi2Unit> Units;

        string to_string(void) const;


    };


    class Boolean : public IXmlNode
    {
    public:
        optional<string> declaredType;
        optional<string> start;

        string to_string(void) const;


    };


    class Integer : public IXmlNode
    {
    public:
        optional<string> declaredType;
        optional<string> start;
        optional<string> quantity;
        optional<int> min;
        optional<int> max;

        string to_string(void) const;


    };


    class String : public IXmlNode
    {
    public:
        optional<string> declaredType;
        optional<string> start;

        string to_string(void) const;


    };


    class Real : public IXmlNode
    {
    public:
        optional<string> declaredType;
        optional<string> quantity;
        optional<string> unit;
        optional<string> displayUnit;
        optional<bool> relativeQuantity;
        optional<double> min;
        optional<double> max;
        optional<double> nominal;
        optional<bool> unbounded;
        optional<double> start;
        optional<unsigned int> derivative;
        optional<bool> reinit;

        string to_string(void) const;


    };


    class Enumeration : public IXmlNode
    {
    public:
        string declaredType;
        optional<string> quantity;
        optional<int> min;
        optional<int> max;
        optional<int> start;

        string to_string(void) const;


    };


    class SimpleTypeEnumerationItem : public IXmlNode
    {
    public:
        string name;
        int value;
        optional<string> description;

        string to_string(void) const;


    };


    class SimpleTypeEnumeration : public IXmlNode
    {
    public:
        optional<string> quantity;
        vector<fmi2::SimpleTypeEnumerationItem> Items;

        string to_string(void) const;


    };


    class fmi2SimpleType : public IXmlNode
    {
    public:
        string name;
        optional<string> description;
        optional<fmi2::Real> Real;
        optional<fmi2::Integer> Integer;
        optional<fmi2::Boolean> Boolean;
        optional<fmi2::String> String;
        optional<fmi2::SimpleTypeEnumeration> Enumeration;

        string to_string(void) const;


    };


    class TypeDefinitions : public IXmlNode
    {
    public:
        vector<fmi2::fmi2SimpleType> SimpleTypes;

        string to_string(void) const;


    };


    class Category : public IXmlNode
    {
    public:
        string name;
        optional<string> description;

        string to_string(void) const;


    };


    class LogCategories : public IXmlNode
    {
    public:
        vector<fmi2::Category> Categories;

        string to_string(void) const;


    };


    class fmi2Annotation : public IXmlNode
    {
    public:
        string annotation;

        string to_string(void) const;


    };


    class VendorAnnotations : public IXmlNode
    {
    public:
        vector<fmi2::fmi2Annotation> Annotations;

        string to_string(void) const;


    };


    class DefaultExperiment : public IXmlNode
    {
    public:
        optional<double> startTime;
        optional<double> stopTime;
        optional<double> tolerance;
        optional<double> stepSize;

        string to_string(void) const;


    };


    class fmi2ScalarVariable : public IXmlNode
    {
    public:
        string name;
        optional<unsigned int> valueReference;
        optional<string> description;
        optional<string> causality;
        optional<string> variability;
        optional<string> initial;
        optional<bool> canHandleMultipleSetPerTimeInstant;
        optional<fmi2::Real> Real;
        optional<fmi2::Integer> Integer;
        optional<fmi2::Boolean> Boolean;
        optional<fmi2::String> String;
        optional<fmi2::Enumeration> Enumeration;
        vector<fmi2::fmi2Annotation> Annotations;

        string to_string(void) const;
        // Custom variables
        int index;

    };


    class Unknown : public IXmlNode
    {
    public:
        int index;
        optional<IntList> dependencies;
        optional<fmi2::DependenciesKindList> dependenciesKind;

        string to_string(void) const;


    };


    class Outputs : public IXmlNode
    {
    public:
        vector<fmi2::Unknown> Unknowns;

        string to_string(void) const;


    };


    class Derivatives : public IXmlNode
    {
    public:
        vector<fmi2::Unknown> Unknowns;

        string to_string(void) const;


    };


    class InitialUnknowns : public IXmlNode
    {
    public:
        vector<fmi2::Unknown> Unknowns;

        string to_string(void) const;


    };


    class ModelStructure : public IXmlNode
    {
    public:
        optional<fmi2::Outputs> Outputs;
        optional<fmi2::Derivatives> Derivatives;
        optional<fmi2::InitialUnknowns> InitialUnknowns;

        string to_string(void) const;


    };


    class ModelVariables : public IXmlNode
    {
    public:
        vector<fmi2::fmi2ScalarVariable> ScalarVariable;

        string to_string(void) const;

        // Custom Functions
        fmi2::fmi2ScalarVariable get_variable(int index);
    };


    class File : public IXmlNode
    {
    public:
        string name;

        string to_string(void) const;


    };


    class SourceFiles : public IXmlNode
    {
    public:
        vector<fmi2::File> Files;

        string to_string(void) const;


    };


    class ModelExchange : public IXmlNode
    {
    public:
        string modelIdentifier;
        optional<bool> needsExecutionTool;
        optional<bool> completedIntegratorStepNotNeeded;
        optional<bool> canBeInstantiatedOnlyOncePerProcess;
        optional<bool> canNotUseMemoryManagementFunctions;
        optional<bool> canGetAndSetFMUstate;
        optional<bool> canSerializeFMUstate;
        optional<bool> providesDirectionalDerivatives;
        optional<fmi2::SourceFiles> SourceFiles;

        string to_string(void) const;


    };


    class CoSimulation : public IXmlNode
    {
    public:
        string modelIdentifier;
        optional<bool> needsExecutionTool;
        optional<bool> canHandleVariableCommunicationStepSize;
        optional<bool> canInterpolateInputs;
        optional<bool> maxOutputDerivativeOrder;
        optional<bool> canRunAsynchronuously;
        optional<bool> canBeInstantiatedOnlyOncePerProcess;
        optional<bool> canNotUseMemoryManagementFunctions;
        optional<bool> canGetAndSetFMUstate;
        optional<bool> canSerializeFMUstate;
        optional<bool> providesDirectionalDerivatives;
        optional<fmi2::SourceFiles> SourceFiles;

        string to_string(void) const;


    };


    class fmi2ModelDescription : public IXmlNode
    {
    public:
        string fmiVersion;
        string modelName;
        string guid;
        optional<string> description;
        optional<string> author;
        optional<string> version;
        optional<string> copyright;
        optional<string> license;
        optional<string> generationTool;
        optional<string> generationDateAndTime;
        optional<string> variableNamingConvention;
        optional<string> numberOfEventIndicators;
        optional<fmi2::ModelExchange> ModelExchange;
        optional<fmi2::CoSimulation> CoSimulation;
        optional<fmi2::UnitDefinitions> UnitDefinitions;
        optional<fmi2::TypeDefinitions> TypeDefinitions;
        optional<fmi2::LogCategories> LogCategories;
        optional<fmi2::DefaultExperiment> DefaultExperiment;
        optional<fmi2::VendorAnnotations> VendorAnnotations;
        fmi2::ModelVariables ModelVariables;
        fmi2::ModelStructure ModelStructure;

        string to_string(void) const;


    };


}
