
#pragma once

#include <optional>
#include <vector>
#include <string>
#include <tuple>

#include "FMI_Enums.hpp"

#include "modelDescription.hpp"

using namespace std;

namespace ssp4cpp::fmi2
{

    class ModelVariables_Ext
    {
    public:
        static fmi2::fmi2ScalarVariable &get_variable(ModelVariables &mv, int index);
    };

    class Unknown_Ext
    {
    public:
        static vector<tuple<int, int, DependenciesKind>> get_dependencies(Unknown &u);

        static vector<tuple<int, int, DependenciesKind>> get_dependencies(Unknown &u, DependenciesKind kind);
    };

}
