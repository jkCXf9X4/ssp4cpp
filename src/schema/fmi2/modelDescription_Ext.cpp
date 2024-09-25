

#include <optional>
#include <vector>
#include <string>

#include "FMI_Enums.hpp"

#include "modelDescription_Ext.hpp"

using namespace std;

namespace ssp4cpp::fmi2
{

    fmi2::fmi2ScalarVariable &ModelVariables_Ext::get_variable(ModelVariables &mv, int index)
    {
        if (index < 0 || index >= mv.ScalarVariable.size())
        {
            throw invalid_argument("Index out of range");
        }

        return mv.ScalarVariable[index];
    }

    vector<tuple<int, int, DependenciesKind>> Unknown_Ext::get_dependencies(Unknown &u, DependenciesKind kind)
    {
        vector<tuple<int, int, DependenciesKind>> result;

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
                result.push_back(make_tuple(u.index, dependency, dependency_kind));
            }
        }

        return result;
    }

    vector<tuple<int, int, DependenciesKind>> Unknown_Ext::get_dependencies(Unknown &u)
    {
        return Unknown_Ext::get_dependencies(u, DependenciesKind::unknown);
    }

}
