
#pragma once

#include <string>

#include <optional>
#include <vector>
#include <string>

#include "FMI_Enums.hpp"

using namespace std;
namespace ssp4cpp::fmi2
{

    class BaseUnit
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
    };
    string to_string(const BaseUnit &obj);
    string to_string(const optional<BaseUnit> &obj);
    string to_string(const vector<BaseUnit> &obj);

    class DisplayUnit
    {
    public:
        string name;
        optional<double> factor;
        optional<double> offset;
    };
    string to_string(const DisplayUnit &obj);
    string to_string(const optional<DisplayUnit> &obj);
    string to_string(const vector<DisplayUnit> &obj);

    class fmi2Unit
    {
    public:
        string name;
        optional<fmi2::BaseUnit> BaseUnit;
        vector<fmi2::DisplayUnit> DisplayUnit;
    };
    string to_string(const fmi2Unit &obj);
    string to_string(const optional<fmi2Unit> &obj);
    string to_string(const vector<fmi2Unit> &obj);

    class UnitDefinitions
    {
    public:
        vector<fmi2Unit> Units;
    };
    string to_string(const UnitDefinitions &obj);
    string to_string(const optional<UnitDefinitions> &obj);
    string to_string(const vector<UnitDefinitions> &obj);

    class Boolean
    {
    public:
        optional<string> declaredType;
        optional<string> start;
    };
    string to_string(const Boolean &obj);
    string to_string(const optional<Boolean> &obj);
    string to_string(const vector<Boolean> &obj);

    class Integer
    {
    public:
        optional<string> declaredType;
        optional<string> start;
        optional<string> quantity;
        optional<int> min;
        optional<int> max;
    };
    string to_string(const Integer &obj);
    string to_string(const optional<Integer> &obj);
    string to_string(const vector<Integer> &obj);

    class String
    {
    public:
        optional<string> declaredType;
        optional<string> start;
    };
    string to_string(const String &obj);
    string to_string(const optional<String> &obj);
    string to_string(const vector<String> &obj);

    class Real
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
    };
    string to_string(const Real &obj);
    string to_string(const optional<Real> &obj);
    string to_string(const vector<Real> &obj);

    class Enumeration
    {
    public:
        string declaredType;
        optional<string> quantity;
        optional<int> min;
        optional<int> max;
        optional<int> start;
    };
    string to_string(const Enumeration &obj);
    string to_string(const optional<Enumeration> &obj);
    string to_string(const vector<Enumeration> &obj);

    class SimpleTypeEnumerationItem
    {
    public:
        string name;
        int value;
        optional<string> description;
    };
    string to_string(const SimpleTypeEnumerationItem &obj);
    string to_string(const optional<SimpleTypeEnumerationItem> &obj);
    string to_string(const vector<SimpleTypeEnumerationItem> &obj);

    class SimpleTypeEnumeration
    {
    public:
        optional<string> quantity;
        vector<SimpleTypeEnumerationItem> item;
    };
    string to_string(const SimpleTypeEnumeration &obj);
    string to_string(const optional<SimpleTypeEnumeration> &obj);
    string to_string(const vector<SimpleTypeEnumeration> &obj);

    class fmi2SimpleType
    {
    public:
        string name;
        optional<string> description;
        optional<fmi2::Real> Real;
        optional<fmi2::Integer> Integer;
        optional<fmi2::Boolean> Boolean;
        optional<fmi2::String> String;
        optional<SimpleTypeEnumeration> Enumeration;
    };
    string to_string(const fmi2SimpleType &obj);
    string to_string(const optional<fmi2SimpleType> &obj);
    string to_string(const vector<fmi2SimpleType> &obj);

    class TypeDefinitions
    {
    public:
        vector<fmi2SimpleType> SimpleTypes;
    };
    string to_string(const TypeDefinitions &obj);
    string to_string(const optional<TypeDefinitions> &obj);
    string to_string(const vector<TypeDefinitions> &obj);

    class Category
    {
    public:
        string name;
        optional<string> description;
    };
    string to_string(const Category &obj);
    string to_string(const optional<Category> &obj);
    string to_string(const vector<Category> &obj);

    class LogCategories
    {
    public:
        vector<Category> categories;
    };
    string to_string(const LogCategories &obj);
    string to_string(const optional<LogCategories> &obj);
    string to_string(const vector<LogCategories> &obj);

    class fmi2Annotation
    {
    public:
        string annotation;
    };
    string to_string(const fmi2Annotation &obj);
    string to_string(const optional<fmi2Annotation> &obj);
    string to_string(const vector<fmi2Annotation> &obj);

    class VendorAnnotations
    {
    public:
        vector<fmi2Annotation> Annotations;
    };
    string to_string(const VendorAnnotations &obj);
    string to_string(const optional<VendorAnnotations> &obj);
    string to_string(const vector<VendorAnnotations> &obj);

    class DefaultExperiment
    {
    public:
        optional<double> startTime;
        optional<double> stopTime;
        optional<double> tolerance;
        optional<double> stepSize;
    };
    string to_string(const DefaultExperiment &obj);
    string to_string(const optional<DefaultExperiment> &obj);
    string to_string(const vector<DefaultExperiment> &obj);

    class fmi2ScalarVariable
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
        vector<fmi2Annotation> Annotations;
    };
    string to_string(const fmi2ScalarVariable &obj);
    string to_string(const optional<fmi2ScalarVariable> &obj);
    string to_string(const vector<fmi2ScalarVariable> &obj);

    class unknown
    {
    public:
        int index;
        vector<unsigned int> dependencies;
        vector<string> dependencies_kind_str;
        vector<DependenciesKind> dependencies_kind;
    };
    string to_string(const unknown &obj);
    string to_string(const optional<unknown> &obj);
    string to_string(const vector<unknown> &obj);

    class ModelStructure
    {
    public:
        vector<unknown> outputs;
        vector<unknown> derivatives;
        vector<unknown> initialUnknowns;
    };
    string to_string(const ModelStructure &obj);
    string to_string(const optional<ModelStructure> &obj);
    string to_string(const vector<ModelStructure> &obj);

    class ModelVariables
    {
    public:
        vector<fmi2ScalarVariable> list;
    };
    string to_string(const ModelVariables &obj);
    string to_string(const optional<ModelVariables> &obj);
    string to_string(const vector<ModelVariables> &obj);

    class File
    {
    public:
        string name;
    };
    string to_string(const File &obj);
    string to_string(const optional<File> &obj);
    string to_string(const vector<File> &obj);

    class ModelExchange
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
        vector<File> SourceFiles;
    };
    string to_string(const ModelExchange &obj);
    string to_string(const optional<ModelExchange> &obj);
    string to_string(const vector<ModelExchange> &obj);

    class CoSimulation
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
        vector<File> SourceFiles;
    };
    string to_string(const CoSimulation &obj);
    string to_string(const optional<CoSimulation> &obj);
    string to_string(const vector<CoSimulation> &obj);

    class fmi2ModelDescription
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
    };
    string to_string(const fmi2ModelDescription &obj);
    string to_string(const optional<fmi2ModelDescription> &obj);
    string to_string(const vector<fmi2ModelDescription> &obj);

}
