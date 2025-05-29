

// This is a generated file, do not alter
// it is based on fmi2_md.toml
#pragma once

#include "common_interface.hpp"
#include "common_xml.hpp"

#include "FMI2_Enums.hpp"


#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::fmi2::md
{
    using namespace ssp4cpp::common::interfaces;
    using namespace ssp4cpp::common::xml;
    using namespace std;




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

        std::string to_string(void) const;
    };

    class DisplayUnit : public IXmlNode
    {
    public:
        string name;
        optional<double> factor;
        optional<double> offset;

        std::string to_string(void) const;
    };

    class fmi2Unit : public IXmlNode
    {
    public:
        string name;
        optional<fmi2::md::BaseUnit> BaseUnit;
        vector<fmi2::md::DisplayUnit> DisplayUnit;

        std::string to_string(void) const;
    };

    class UnitDefinitions : public IXmlNode
    {
    public:
        vector<fmi2::md::fmi2Unit> Units;

        std::string to_string(void) const;
    };

    class Boolean : public IXmlNode
    {
    public:
        optional<string> declaredType;
        optional<string> start;

        std::string to_string(void) const;
    };

    class Integer : public IXmlNode
    {
    public:
        optional<string> declaredType;
        optional<string> start;
        optional<string> quantity;
        optional<int> min;
        optional<int> max;

        std::string to_string(void) const;
    };

    class String : public IXmlNode
    {
    public:
        optional<string> declaredType;
        optional<string> start;

        std::string to_string(void) const;
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

        std::string to_string(void) const;
    };

    class Enumeration : public IXmlNode
    {
    public:
        string declaredType;
        optional<string> quantity;
        optional<int> min;
        optional<int> max;
        optional<int> start;

        std::string to_string(void) const;
    };

    class SimpleTypeEnumerationItem : public IXmlNode
    {
    public:
        string name;
        int value;
        optional<string> description;

        std::string to_string(void) const;
    };

    class SimpleTypeEnumeration : public IXmlNode
    {
    public:
        optional<string> quantity;
        vector<fmi2::md::SimpleTypeEnumerationItem> Items;

        std::string to_string(void) const;
    };

    class fmi2SimpleType : public IXmlNode
    {
    public:
        string name;
        optional<string> description;
        optional<fmi2::md::Real> Real;
        optional<fmi2::md::Integer> Integer;
        optional<fmi2::md::Boolean> Boolean;
        optional<fmi2::md::String> String;
        optional<fmi2::md::SimpleTypeEnumeration> Enumeration;

        std::string to_string(void) const;
    };

    class TypeDefinitions : public IXmlNode
    {
    public:
        vector<fmi2::md::fmi2SimpleType> SimpleTypes;

        std::string to_string(void) const;
    };

    class Category : public IXmlNode
    {
    public:
        string name;
        optional<string> description;

        std::string to_string(void) const;
    };

    class LogCategories : public IXmlNode
    {
    public:
        vector<fmi2::md::Category> Categories;

        std::string to_string(void) const;
    };

    class fmi2Annotation : public IXmlNode
    {
    public:
        string annotation;

        std::string to_string(void) const;
    };

    class VendorAnnotations : public IXmlNode
    {
    public:
        vector<fmi2::md::fmi2Annotation> Annotations;

        std::string to_string(void) const;
    };

    class DefaultExperiment : public IXmlNode
    {
    public:
        optional<double> startTime;
        optional<double> stopTime;
        optional<double> tolerance;
        optional<double> stepSize;

        std::string to_string(void) const;
    };

    class fmi2ScalarVariable : public IXmlNode
    {
    public:
        string name;
        optional<unsigned int> valueReference;
        optional<string> description;
        optional<fmi2::md::Causality> causality;
        optional<fmi2::md::Variability> variability;
        optional<fmi2::md::Initial> initial;
        optional<bool> canHandleMultipleSetPerTimeInstant;
        optional<fmi2::md::Real> Real;
        optional<fmi2::md::Integer> Integer;
        optional<fmi2::md::Boolean> Boolean;
        optional<fmi2::md::String> String;
        optional<fmi2::md::Enumeration> Enumeration;
        vector<fmi2::md::fmi2Annotation> Annotations;

        std::string to_string(void) const;
    };

    class Unknown : public IXmlNode
    {
    public:
        int index;
        optional<IntXmlList> dependencies;
        optional<fmi2::md::DependenciesKindList> dependenciesKind;

        std::string to_string(void) const;
    };

    class Outputs : public IXmlNode
    {
    public:
        vector<fmi2::md::Unknown> Unknowns;

        std::string to_string(void) const;
    };

    class Derivatives : public IXmlNode
    {
    public:
        vector<fmi2::md::Unknown> Unknowns;

        std::string to_string(void) const;
    };

    class InitialUnknowns : public IXmlNode
    {
    public:
        vector<fmi2::md::Unknown> Unknowns;

        std::string to_string(void) const;
    };

    class ModelStructure : public IXmlNode
    {
    public:
        optional<fmi2::md::Outputs> Outputs;
        optional<fmi2::md::Derivatives> Derivatives;
        optional<fmi2::md::InitialUnknowns> InitialUnknowns;

        std::string to_string(void) const;
    };

    class ModelVariables : public IXmlNode
    {
    public:
        vector<fmi2::md::fmi2ScalarVariable> ScalarVariable;

        std::string to_string(void) const;
    };

    class File : public IXmlNode
    {
    public:
        string name;

        std::string to_string(void) const;
    };

    class SourceFiles : public IXmlNode
    {
    public:
        vector<fmi2::md::File> Files;

        std::string to_string(void) const;
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
        optional<fmi2::md::SourceFiles> SourceFiles;

        std::string to_string(void) const;
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
        optional<fmi2::md::SourceFiles> SourceFiles;

        std::string to_string(void) const;
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
        optional<fmi2::md::ModelExchange> ModelExchange;
        optional<fmi2::md::CoSimulation> CoSimulation;
        optional<fmi2::md::UnitDefinitions> UnitDefinitions;
        optional<fmi2::md::TypeDefinitions> TypeDefinitions;
        optional<fmi2::md::LogCategories> LogCategories;
        optional<fmi2::md::DefaultExperiment> DefaultExperiment;
        optional<fmi2::md::VendorAnnotations> VendorAnnotations;
        fmi2::md::ModelVariables ModelVariables;
        fmi2::md::ModelStructure ModelStructure;

        std::string to_string(void) const;
    };

}
