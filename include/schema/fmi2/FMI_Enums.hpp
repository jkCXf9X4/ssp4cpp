
#pragma once

#include <string>
#include <optional>
#include <vector>

using namespace std;
namespace ssp4cpp::fmi2
{
    enum class Causality
    {
        Parameter,
        CalculatedParameter,
        Input,
        Output,
        Local,
        Independent,
        Unknown
    };
    string to_string(const Causality &obj);
    string to_string(const optional<Causality> &obj);
    string to_string(const vector<Causality> &obj);

    Causality causality_from_string(const string &str);

    enum class Variability
    {
        constant,
        fixed,
        tunable,
        discrete,
        continuous,
        unknown
    };
    string to_string(const Variability &obj);
    string to_string(const optional<Variability> &obj);
    string to_string(const vector<Variability> &obj);

    Variability variability_from_string(const string &str);

    enum class Initial
    {
        exact,
        approx,
        calculated,
        unknown
    };
    string to_string(const Initial &obj);
    string to_string(const optional<Initial> &obj);
    string to_string(const vector<Initial> &obj);

    Initial initial_from_string(const string &str);

    enum class DependenciesKind
    {
        dependent,
        constant,
        fixed,
        tunable,
        discrete
    };

    string to_string(const DependenciesKind &obj);
    string to_string(const optional<DependenciesKind> &obj);
    string to_string(const vector<DependenciesKind> &obj);

    Initial dependenciesKind_from_string(const string &str);
}