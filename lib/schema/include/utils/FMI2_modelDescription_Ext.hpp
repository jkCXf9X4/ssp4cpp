
#pragma once

#include "common_log.hpp"

#include "FMI2_Enums.hpp"
#include "FMI2_modelDescription.hpp"

#include <vector>
#include <string>
#include <tuple>

namespace ssp4cpp::fmi2::ext
{
    using namespace ssp4cpp::fmi2::md;

    namespace model_variables
    {
        using DataType = ssp4cpp::fmi2::md::Type;

        inline auto log = common::Logger("fmi2.ext.model_variables", common::LogLevel::debug);
        /** @brief Retrieve a variable by index from the model variables list. */
        fmi2ScalarVariable *get_variable(ModelVariables &mv, int index);

        fmi2ScalarVariable *get_variable_by_name(ModelVariables &mv, std::string name);

        DataType get_variable_type(fmi2ScalarVariable &var);

        void *get_variable_start_value(fmi2ScalarVariable &var);
    }

    namespace dependency
    {
        inline auto log = common::Logger("fmi2.ext.dependency", common::LogLevel::debug);

        using IndexDependencyCoupling = std::tuple<int, int, DependenciesKind>;
        using VariableDependencyCoupling = std::tuple<fmi2ScalarVariable *, fmi2ScalarVariable *, DependenciesKind>;

        // Unknowns
        /** @brief Get variable dependencies for an Unknown by index. */
        std::vector<IndexDependencyCoupling> get_dependencies_index(Unknown &u);

        /** @brief Get variable dependencies for an Unknown filtered by kind. */
        std::vector<IndexDependencyCoupling> get_dependencies_index(Unknown &u, DependenciesKind kind);

        /** @brief Resolve variable dependencies for a single Unknown. */
        std::vector<VariableDependencyCoupling> get_dependencies_variables(Unknown &u, ModelVariables &mv);

        /** @brief Resolve variable dependencies filtered by kind. */
        std::vector<VariableDependencyCoupling> get_dependencies_variables(Unknown &u, ModelVariables &mv, DependenciesKind kind);

        /** @brief Resolve dependencies for multiple Unknowns filtered by kind. */
        std::vector<VariableDependencyCoupling> get_dependencies_variables(std::vector<Unknown> &us, ModelVariables &mv, DependenciesKind kind);
    }

}
