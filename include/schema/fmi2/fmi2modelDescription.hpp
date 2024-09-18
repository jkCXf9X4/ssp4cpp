
#pragma once

#include <string>

#include <optional>
#include <vector>
// #include "node_base.hpp"

namespace ssp4cpp::fmi2
{
    using namespace std;
    
    class DefaultExperiment 
    {
    public:
        optional<double> startTime;
        optional<double> stopTime;
        optional<double> tolerance;
        optional<double> stepSize;
    };
    string to_string(const DefaultExperiment &obj);

    class fmi2ModelDescription
    {
    public:
        string fmiVersion;
        string modelName;
        // string guid;
        // optional<string> guid;
        // optional<string> description;
        // optional<string> author;
        // optional<string> version;
        // optional<string> copyright;
        // optional<string> guid;
        // optional<string> license;
        // optional<string> generationTool;
        // optional<string> generationTool;
        // optional<string> generationDateAndTime;
        // optional<string> variableNamingConvention;
        // optional<string> numberOfEventIndicators;

        // optional<ModelExchange> ModelExchange;
        // optional<CoSimulation> CoSimulation;
        // optional<UnitDefinitions> UnitDefinitions;
        // optional<TypeDefinitions> TypeDefinitions;
        // optional<LogCategories> LogCategories;
        optional<DefaultExperiment> defaultExperiment;
        // optional<VendorAnnotations> VendorAnnotations;
        // ModelVariables ModelVariables;
        // ModelStructure ModelStructure;

    };
    
    string to_string(const fmi2ModelDescription &obj);
}
