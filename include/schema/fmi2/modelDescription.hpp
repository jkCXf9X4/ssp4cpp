
#pragma once

#include <string>

#include <optional>
#include <vector>
#include <string>

#include "FMI_Enums.hpp"

namespace ssp4cpp::fmi2
{
    using namespace std;

    struct BaseUnit
    {
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

    struct DisplayUnit
    {
        string name;
        optional<double> factor;
        optional<double> offset;
    };

    struct fmi2Unit
    {
        string name;
        optional<fmi2::BaseUnit> BaseUnit;
        vector<fmi2::DisplayUnit> DisplayUnit;
    };

    struct UnitDefinitions
    {
        vector<fmi2Unit> Units;
    };

    struct Boolean
    {
        optional<string> declaredType;
        optional<string> start;
    };

    struct Integer
    {
        optional<string> declaredType;
        optional<string> start;
        optional<string> quantity;
        optional<int> min;
        optional<int> max;
    };

    struct String
    {
        optional<string> declaredType;
        optional<string> start;
    };

    struct Real
    {
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

    struct Enumeration
    {
        string declaredType;
        optional<string> quantity;
        optional<int> min;
        optional<int> max;
        optional<int> start;
    };

    struct SimpleTypeEnumerationItem
    {
        string name;
        int value;
        optional<string> description;
    };

    struct SimpleTypeEnumeration
    {
        optional<string> quantity;
        vector<SimpleTypeEnumerationItem> item;
    };

    struct fmi2SimpleType
    {
        string name;
        optional<string> description;

        optional<fmi2::Real> Real;
        optional<fmi2::Integer> Integer;
        optional<fmi2::Boolean> Boolean; // not sure
        optional<fmi2::String> String;   // not sure
        optional<SimpleTypeEnumeration> Enumeration;
    };

    struct TypeDefinitions
    {
        vector<fmi2SimpleType> SimpleTypes;
    };

    struct Category
    {
        string name;
        optional<string> description;
    };

    struct LogCategories
    {
        vector<Category> categories;
    };

    struct fmi2Annotation
    {
        string annotation; // parse everything as string
    };

    struct VendorAnnotations
    {
        vector<fmi2Annotation> Annotations;
    };

    struct DefaultExperiment
    {
        optional<double> startTime;
        optional<double> stopTime;
        optional<double> tolerance;
        optional<double> stepSize;
    };

    struct fmi2ScalarVariable
    {
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

    struct unknown
    {
        int index;
        std::vector<unsigned int> dependencies;
        std::vector<std::string> dependencies_kind_str;
        std::vector<DependenciesKind> dependencies_kind;
    };

    struct ModelStructure
    {
        vector<unknown> outputs;
        vector<unknown> derivatives;
        vector<unknown> initialUnknowns;
    };

    struct ModelVariables
    {
        vector<fmi2ScalarVariable> list;
    };

    struct File
    {
        string name;
    };

    struct ModelExchange
    {
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

    struct CoSimulation
    {
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

    struct fmi2ModelDescription
    {
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

}
