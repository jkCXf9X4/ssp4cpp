

#include <optional>
#include <vector>
#include <string>

#include "FMI_Enums.hpp"

#include "modelDescription_Ext.hpp"
#include <iostream>

using namespace std;

namespace ssp4cpp::fmi2
{

    fmi2ScalarVariable &ModelVariables_Ext::get_variable(ModelVariables &mv, int index)
    {
        if (index < 0 || index >= mv.ScalarVariable.size())
        {
            throw invalid_argument("Index out of range");
        }

        // index start at 1
        return mv.ScalarVariable[index - 1];
    }

    vector<IndexDependencyCoupling> Unknown_Ext::get_dependencies_index(Unknown &u)
    {
        return get_dependencies_index(u, DependenciesKind::unknown);
    }

    // output index, dependency index , kind
    vector<IndexDependencyCoupling> Unknown_Ext::get_dependencies_index(Unknown &u, DependenciesKind kind)
    {
        auto result = vector<IndexDependencyCoupling>();

        if (!u.dependencies.has_value())
        {
            return result;
        }

        for (int i = 0; i < u.dependencies.value().list.size(); i++)
        {
            auto dependency = u.dependencies.value().list[i];
            auto dependency_kind = u.dependenciesKind.value().list[i];

            if (kind == DependenciesKind::unknown || dependency_kind == kind)
            {
                auto t = make_tuple(u.index, dependency, dependency_kind);
                result.push_back(t);
            }
        }

        return result;
    }

    vector<VariableDependencyCoupling> Unknown_Ext::get_dependencies_variables(Unknown &u, ModelVariables &mv)
    {
        return get_dependencies_variables(u, mv, DependenciesKind::unknown);
    }

    vector<VariableDependencyCoupling> Unknown_Ext::get_dependencies_variables(Unknown &u, ModelVariables &mv, DependenciesKind kind)
    {
        auto result = vector<VariableDependencyCoupling>();

        auto dependencies = Unknown_Ext::get_dependencies_index(u, kind);

        for (auto [index, dependency, kind] : dependencies)
        {
            auto& output = ModelVariables_Ext::get_variable(mv, index);
            auto& dep = ModelVariables_Ext::get_variable(mv, dependency);

            auto t = VariableDependencyCoupling(output, dep, kind);
            result.push_back(t);
        }
        return result;
    }

    vector<VariableDependencyCoupling> Unknown_Ext::get_dependencies_variables(vector<Unknown> &us, ModelVariables &mv, DependenciesKind kind)
    {
        auto result = vector<VariableDependencyCoupling>();

        for (auto& u : us)
        {
            auto dependencies = Unknown_Ext::get_dependencies_variables(u, mv, kind);
            result.insert(result.end(), dependencies.begin(), dependencies.end());
        }
        return result;
    }

} // namespace ssp4cpp::fmi2
