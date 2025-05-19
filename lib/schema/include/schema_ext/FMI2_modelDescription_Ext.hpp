
#pragma once

#include "common_log.hpp"

#include "FMI2_Enums.hpp"
#include "FMI2_modelDescription.hpp"

#include <vector>
#include <string>
#include <tuple>

using namespace std;

namespace ssp4cpp::fmi2::ext
{
    using namespace ssp4cpp::fmi2::md;

    namespace model_variables
    {
        inline auto log = common::Logger("fmi2.ext.model_variables", common::LogLevel::debug);

        fmi2ScalarVariable* get_variable(ModelVariables &mv, int index);
    }


    namespace dependency
    {
        inline auto log = common::Logger("fmi2.ext.dependency", common::LogLevel::debug);
        
        using IndexDependencyCoupling = std::tuple<int, int, DependenciesKind>;
        using VariableDependencyCoupling = std::tuple<fmi2ScalarVariable*, fmi2ScalarVariable*, DependenciesKind>;
    
    
        // Unknowns
        vector<IndexDependencyCoupling> get_dependencies_index(Unknown &u);
    
        vector<IndexDependencyCoupling> get_dependencies_index(Unknown &u, DependenciesKind kind);
    
        vector<VariableDependencyCoupling> get_dependencies_variables(Unknown &u, ModelVariables &mv);
    
        vector<VariableDependencyCoupling> get_dependencies_variables(Unknown &u, ModelVariables &mv, DependenciesKind kind);
    
        vector<VariableDependencyCoupling> get_dependencies_variables(vector<Unknown> &us, ModelVariables &mv, DependenciesKind kind);
    }

}
