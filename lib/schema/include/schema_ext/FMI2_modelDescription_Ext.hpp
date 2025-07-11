
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
    
    inline auto log = common::Logger("fmi2.ext", common::LogLevel::debug);


    namespace model_variables
    {
        inline auto log = common::Logger("fmi2.ext.model_variables", common::LogLevel::debug);
        /** @brief Retrieve a variable by index from the model variables list. */
        fmi2ScalarVariable* get_variable(ModelVariables &mv, int index);
    }


    namespace dependency
    {
        inline auto log = common::Logger("fmi2.ext.dependency", common::LogLevel::debug);
        
        using IndexDependencyCoupling = std::tuple<int, int, DependenciesKind>;
        using VariableDependencyCoupling = std::tuple<fmi2ScalarVariable*, fmi2ScalarVariable*, DependenciesKind>;
    
    
        // Unknowns
        /** @brief Get variable dependencies for an Unknown by index. */
        vector<IndexDependencyCoupling> get_dependencies_index(Unknown &u);
    
        /** @brief Get variable dependencies for an Unknown filtered by kind. */
        vector<IndexDependencyCoupling> get_dependencies_index(Unknown &u, DependenciesKind kind);
    
        /** @brief Resolve variable dependencies for a single Unknown. */
        vector<VariableDependencyCoupling> get_dependencies_variables(Unknown &u, ModelVariables &mv);
    
        /** @brief Resolve variable dependencies filtered by kind. */
        vector<VariableDependencyCoupling> get_dependencies_variables(Unknown &u, ModelVariables &mv, DependenciesKind kind);
    
        /** @brief Resolve dependencies for multiple Unknowns filtered by kind. */
        vector<VariableDependencyCoupling> get_dependencies_variables(vector<Unknown> &us, ModelVariables &mv, DependenciesKind kind);
    }

}
