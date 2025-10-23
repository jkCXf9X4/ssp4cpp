

// This is a generated file, do not alter
// it is based on fmi2_md.toml
#pragma once

#include "ssp4cpp/utils/interface.hpp"
#include "ssp4cpp/utils/xml.hpp"

#include "ssp4cpp/schema/fmi2/FMI2_Enums.hpp"


#include <string>
#include <vector>
#include <optional>

namespace ssp4cpp::fmi2::md
{
    using namespace utils::interfaces;
    using namespace utils::xml;




    class BaseUnit : public IXmlNode
    {
    public:
        std::optional<int> kg;
        std::optional<int> m;
        std::optional<int> s;
        std::optional<int> a;
        std::optional<int> k;
        std::optional<int> mol;
        std::optional<int> cd;
        std::optional<int> rad;
        std::optional<double> factor;
        std::optional<double> offset;

        std::string to_string(void) const;
    };

    class DisplayUnit : public IXmlNode
    {
    public:
        std::string name;
        std::optional<double> factor;
        std::optional<double> offset;

        std::string to_string(void) const;
    };

    class fmi2Unit : public IXmlNode
    {
    public:
        std::string name;
        std::optional<fmi2::md::BaseUnit> BaseUnit;
        std::vector<fmi2::md::DisplayUnit> DisplayUnit;

        std::string to_string(void) const;
    };

    class UnitDefinitions : public IXmlNode
    {
    public:
        std::vector<fmi2::md::fmi2Unit> Units;

        std::string to_string(void) const;
    };

    class Boolean : public IXmlNode
    {
    public:
        std::optional<std::string> declaredType;
        std::optional<bool> start;

        std::string to_string(void) const;
    };

    class Integer : public IXmlNode
    {
    public:
        std::optional<std::string> declaredType;
        std::optional<int> start;
        std::optional<std::string> quantity;
        std::optional<int> min;
        std::optional<int> max;

        std::string to_string(void) const;
    };

    class String : public IXmlNode
    {
    public:
        std::optional<std::string> declaredType;
        std::optional<std::string> start;

        std::string to_string(void) const;
    };

    class Real : public IXmlNode
    {
    public:
        std::optional<std::string> declaredType;
        std::optional<std::string> quantity;
        std::optional<std::string> unit;
        std::optional<std::string> displayUnit;
        std::optional<bool> relativeQuantity;
        std::optional<double> min;
        std::optional<double> max;
        std::optional<double> nominal;
        std::optional<bool> unbounded;
        std::optional<double> start;
        std::optional<unsigned int> derivative;
        std::optional<bool> reinit;

        std::string to_string(void) const;
    };

    class Enumeration : public IXmlNode
    {
    public:
        std::string declaredType;
        std::optional<std::string> quantity;
        std::optional<int> min;
        std::optional<int> max;
        std::optional<int> start;

        std::string to_string(void) const;
    };

    class SimpleTypeEnumerationItem : public IXmlNode
    {
    public:
        std::string name;
        int value;
        std::optional<std::string> description;

        std::string to_string(void) const;
    };

    class SimpleTypeEnumeration : public IXmlNode
    {
    public:
        std::optional<std::string> quantity;
        std::vector<fmi2::md::SimpleTypeEnumerationItem> Items;

        std::string to_string(void) const;
    };

    class fmi2SimpleType : public IXmlNode
    {
    public:
        std::string name;
        std::optional<std::string> description;
        std::optional<fmi2::md::Real> Real;
        std::optional<fmi2::md::Integer> Integer;
        std::optional<fmi2::md::Boolean> Boolean;
        std::optional<fmi2::md::String> String;
        std::optional<fmi2::md::SimpleTypeEnumeration> Enumeration;

        std::string to_string(void) const;
    };

    class TypeDefinitions : public IXmlNode
    {
    public:
        std::vector<fmi2::md::fmi2SimpleType> SimpleTypes;

        std::string to_string(void) const;
    };

    class Category : public IXmlNode
    {
    public:
        std::string name;
        std::optional<std::string> description;

        std::string to_string(void) const;
    };

    class LogCategories : public IXmlNode
    {
    public:
        std::vector<fmi2::md::Category> Categories;

        std::string to_string(void) const;
    };

    class fmi2Annotation : public IXmlNode
    {
    public:
        std::string annotation;

        std::string to_string(void) const;
    };

    class VendorAnnotations : public IXmlNode
    {
    public:
        std::vector<fmi2::md::fmi2Annotation> Annotations;

        std::string to_string(void) const;
    };

    class DefaultExperiment : public IXmlNode
    {
    public:
        std::optional<double> startTime;
        std::optional<double> stopTime;
        std::optional<double> tolerance;
        std::optional<double> stepSize;

        std::string to_string(void) const;
    };

    class fmi2ScalarVariable : public IXmlNode
    {
    public:
        std::string name;
        std::optional<unsigned int> valueReference;
        std::optional<std::string> description;
        std::optional<fmi2::md::Causality> causality;
        std::optional<fmi2::md::Variability> variability;
        std::optional<fmi2::md::Initial> initial;
        std::optional<bool> canHandleMultipleSetPerTimeInstant;
        std::optional<fmi2::md::Real> Real;
        std::optional<fmi2::md::Integer> Integer;
        std::optional<fmi2::md::Boolean> Boolean;
        std::optional<fmi2::md::String> String;
        std::optional<fmi2::md::Enumeration> Enumeration;
        std::vector<fmi2::md::fmi2Annotation> Annotations;

        std::string to_string(void) const;
    };

    class Unknown : public IXmlNode
    {
    public:
        int index;
        std::optional<IntXmlList> dependencies;
        std::optional<fmi2::md::DependenciesKindList> dependenciesKind;

        std::string to_string(void) const;
    };

    class Outputs : public IXmlNode
    {
    public:
        std::vector<fmi2::md::Unknown> Unknowns;

        std::string to_string(void) const;
    };

    class Derivatives : public IXmlNode
    {
    public:
        std::vector<fmi2::md::Unknown> Unknowns;

        std::string to_string(void) const;
    };

    class InitialUnknowns : public IXmlNode
    {
    public:
        std::vector<fmi2::md::Unknown> Unknowns;

        std::string to_string(void) const;
    };

    class ModelStructure : public IXmlNode
    {
    public:
        std::optional<fmi2::md::Outputs> Outputs;
        std::optional<fmi2::md::Derivatives> Derivatives;
        std::optional<fmi2::md::InitialUnknowns> InitialUnknowns;

        std::string to_string(void) const;
    };

    class ModelVariables : public IXmlNode
    {
    public:
        std::vector<fmi2::md::fmi2ScalarVariable> ScalarVariable;

        std::string to_string(void) const;
    };

    class File : public IXmlNode
    {
    public:
        std::string name;

        std::string to_string(void) const;
    };

    class SourceFiles : public IXmlNode
    {
    public:
        std::vector<fmi2::md::File> Files;

        std::string to_string(void) const;
    };

    class ModelExchange : public IXmlNode
    {
    public:
        std::string modelIdentifier;
        std::optional<bool> needsExecutionTool;
        std::optional<bool> completedIntegratorStepNotNeeded;
        std::optional<bool> canBeInstantiatedOnlyOncePerProcess;
        std::optional<bool> canNotUseMemoryManagementFunctions;
        std::optional<bool> canGetAndSetFMUstate;
        std::optional<bool> canSerializeFMUstate;
        std::optional<bool> providesDirectionalDerivatives;
        std::optional<fmi2::md::SourceFiles> SourceFiles;

        std::string to_string(void) const;
    };

    class CoSimulation : public IXmlNode
    {
    public:
        std::string modelIdentifier;
        std::optional<bool> needsExecutionTool;
        std::optional<bool> canHandleVariableCommunicationStepSize;
        std::optional<bool> canInterpolateInputs;
        std::optional<bool> maxOutputDerivativeOrder;
        std::optional<bool> canRunAsynchronuously;
        std::optional<bool> canBeInstantiatedOnlyOncePerProcess;
        std::optional<bool> canNotUseMemoryManagementFunctions;
        std::optional<bool> canGetAndSetFMUstate;
        std::optional<bool> canSerializeFMUstate;
        std::optional<bool> providesDirectionalDerivatives;
        std::optional<fmi2::md::SourceFiles> SourceFiles;

        std::string to_string(void) const;
    };

    class fmi2ModelDescription : public IXmlNode
    {
    public:
        std::string fmiVersion;
        std::string modelName;
        std::string guid;
        std::optional<std::string> description;
        std::optional<std::string> author;
        std::optional<std::string> version;
        std::optional<std::string> copyright;
        std::optional<std::string> license;
        std::optional<std::string> generationTool;
        std::optional<std::string> generationDateAndTime;
        std::optional<std::string> variableNamingConvention;
        std::optional<std::string> numberOfEventIndicators;
        std::optional<fmi2::md::ModelExchange> ModelExchange;
        std::optional<fmi2::md::CoSimulation> CoSimulation;
        std::optional<fmi2::md::UnitDefinitions> UnitDefinitions;
        std::optional<fmi2::md::TypeDefinitions> TypeDefinitions;
        std::optional<fmi2::md::LogCategories> LogCategories;
        std::optional<fmi2::md::DefaultExperiment> DefaultExperiment;
        std::optional<fmi2::md::VendorAnnotations> VendorAnnotations;
        fmi2::md::ModelVariables ModelVariables;
        fmi2::md::ModelStructure ModelStructure;

        std::string to_string(void) const;
    };

}
