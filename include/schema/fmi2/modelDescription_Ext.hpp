
#pragma once

#include "FMI_Enums.hpp"
#include "modelDescription.hpp"

#include <optional>
#include <vector>
#include <string>
#include <tuple>

using namespace std;

namespace ssp4cpp::fmi2
{

    class ModelVariables_Ext
    {
    public:
        static fmi2::fmi2ScalarVariable &get_variable(ModelVariables &mv, int index);
    };

    using IndexDependencyCoupling = tuple<int, int, DependenciesKind>;
    using VariableDependencyCoupling = tuple<fmi2ScalarVariable &, fmi2ScalarVariable &, DependenciesKind>;

    class Unknown_Ext
    {

    public:
        static vector<IndexDependencyCoupling> get_dependencies_index(Unknown &u);

        static vector<IndexDependencyCoupling> get_dependencies_index(Unknown &u, DependenciesKind kind);

        static vector<VariableDependencyCoupling> get_dependencies_variables(Unknown &u, ModelVariables &mv);

        static vector<VariableDependencyCoupling> get_dependencies_variables(Unknown &u, ModelVariables &mv, DependenciesKind kind);

        static vector<VariableDependencyCoupling> get_dependencies_variables(vector<Unknown> &us, ModelVariables &mv, DependenciesKind kind);
    };

}
