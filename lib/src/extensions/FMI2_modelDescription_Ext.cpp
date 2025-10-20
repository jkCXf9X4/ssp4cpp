
#include "FMI2_modelDescription_Ext.hpp"

#include <optional>
#include <vector>
#include <string>

#include <iostream>

namespace ssp4cpp::fmi2::ext
{
    using namespace std;
    using namespace ssp4cpp::fmi2::md;

    namespace model_variables
    {
        fmi2ScalarVariable *get_variable(ModelVariables &mv, int index)
        {
            if (index < 0 || index >= mv.ScalarVariable.size())
            {
                throw invalid_argument("Index out of range");
            }

            // index start at 1
            return &mv.ScalarVariable[index - 1];
        }

        fmi2ScalarVariable *get_variable_by_name(ModelVariables &mv, std::string name)
        {
            for (auto &var : mv.ScalarVariable)
            {
                if (var.name == name)
                {
                    return &var;
                }
            }
            log(trace)("[{}] No variable found for name {}", __func__, name);
            return nullptr;
        }

        DataType get_variable_type(fmi2ScalarVariable &var)
        {
            if (var.Boolean.has_value())
            {
                return DataType::boolean;
            }
            else if (var.Enumeration.has_value())
            {
                return DataType::enumeration;
            }
            else if (var.Integer.has_value())
            {
                return DataType::integer;
            }
            else if (var.Real.has_value())
            {
                return DataType::real;
            }
            else if (var.String.has_value())
            {
                return DataType::string;
            }
            else
            {
                throw runtime_error("Unknown type");
            }
        }

        void *get_variable_start_value(fmi2ScalarVariable &var)
        {
            if (var.Boolean.has_value() && var.Boolean.value().start.has_value())
            {
                return &var.Boolean.value().start.value();
            }
            else if (var.Enumeration.has_value()&& var.Enumeration.value().start.has_value())
            {
                return &var.Enumeration.value().start.value();
            }
            else if (var.Integer.has_value()&& var.Integer.value().start.has_value())
            {
                return &var.Integer.value().start.value();
            }
            else if (var.Real.has_value()&& var.Real.value().start.has_value())
            {
                return &var.Real.value().start.value();
            }
            else if (var.String.has_value()&& var.String.value().start.has_value())
            {
                return &var.String.value().start.value();
            }
            return nullptr;
        }
    }

    namespace dependency
    {

        vector<IndexDependencyCoupling> get_dependencies_index(Unknown &u)
        {
            return get_dependencies_index(u, DependenciesKind::unknown);
        }

        // output index, dependency index , kind
        vector<IndexDependencyCoupling> get_dependencies_index(Unknown &u, DependenciesKind kind)
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

        vector<VariableDependencyCoupling> get_dependencies_variables(Unknown &u, ModelVariables &mv)
        {
            // should add 'all'
            return get_dependencies_variables(u, mv, DependenciesKind::unknown);
        }

        vector<VariableDependencyCoupling> get_dependencies_variables(Unknown &u, ModelVariables &mv, DependenciesKind kind)
        {
            auto result = vector<VariableDependencyCoupling>();

            auto dependencies = get_dependencies_index(u, kind);

            for (auto [index, dependency, kind] : dependencies)
            {
                auto output = ext::model_variables::get_variable(mv, index);
                auto dep = ext::model_variables::get_variable(mv, dependency);

                auto t = VariableDependencyCoupling(output, dep, kind);
                result.push_back(t);
            }
            return result;
        }

        vector<VariableDependencyCoupling> get_dependencies_variables(vector<Unknown> &us, ModelVariables &mv, DependenciesKind kind)
        {
            auto result = vector<VariableDependencyCoupling>();

            for (auto &u : us)
            {
                auto dependencies = get_dependencies_variables(u, mv, kind);
                result.insert(result.end(), dependencies.begin(), dependencies.end());
            }
            return result;
        }
    }
}
