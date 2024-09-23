
#pragma once

#include <string>
#include <optional>
#include <vector>

using namespace std;
namespace ssp4cpp::fmi2
{
    enum class Causality
    {
        parameter,
        calculatedParameter,
        input,
        output,
        local,
        independent,
        unknown
    };
    string to_string(const Causality &obj);

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

    Variability variability_from_string(const string &str);

    enum class Initial
    {
        exact,
        approx,
        calculated,
        unknown
    };
    string to_string(const Initial &obj);

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

    Initial dependenciesKind_from_string(const string &str);

    enum class LogCategory
    {
        logEvents,
        logSingularLinearSystems,
        logNonlinearSystems,
        logDynamicStateSelection,
        logStatusWarning,
        logStatusDiscard,
        logStatusError,
        logStatusFatal,
        logStatusPending,
        logAll
    };

    string to_string(const LogCategory &obj);

}