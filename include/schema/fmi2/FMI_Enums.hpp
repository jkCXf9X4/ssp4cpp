#pragma once

#include <string>
#include <optional>
#include <vector>

#include "IXmlNode.hpp"
#include "IXmlNodeList.hpp"

using namespace std;

using namespace ssp4cpp::interfaces;

namespace ssp4cpp::fmi2
{
    class Causality : public IReadWrite
    {
    public:
        enum Value : int
        {
            parameter,
            calculatedParameter,
            input,
            output,
            local,
            independent,
            unknown
        };

        Causality() = default;
        constexpr Causality(Value value) : value(value) {}

        string to_string() const override
        {
            switch (value)
            {
            case Value::parameter:
                return "parameter";
            case Value::calculatedParameter:
                return "calculatedParameter";
            case Value::input:
                return "input";
            case Value::output:
                return "output";
            case Value::local:
                return "local";
            case Value::independent:
                return "independent";
            default:
                return "unknown";
            }
        }

        void from_string(const string &str) override
        {
            if (str == "parameter")
            {
                value = Value::parameter;
            }
            else if (str == "calculatedParameter")
            {
                value = Value::calculatedParameter;
            }
            else if (str == "input")
            {
                value = Value::input;
            }
            else if (str == "output")
            {
                value = Value::output;
            }
            else if (str == "local")
            {
                value = Value::local;
            }
            else if (str == "independent")
            {
                value = Value::independent;
            }
            else
            {
                value = Value::unknown;
            }
        }

    private:
        Value value;
    };

    class Variability : public IReadWrite
    {
    public:
        enum Value : int
        {
            constant,
            fixed,
            tunable,
            discrete,
            continuous,
            unknown
        };

        Variability() = default;
        constexpr Variability(Value value) : value(value) {}

        string to_string() const override
        {
            switch (value)
            {
            case Value::constant:
                return "constant";
            case Value::fixed:
                return "fixed";
            case Value::tunable:
                return "tunable";
            case Value::discrete:
                return "discrete";
            case Value::continuous:
                return "continuous";
            default:
                return "unknown";
            }
        }

        void from_string(const string &str) override
        {
            if (str == "constant")
            {
                value = Value::constant;
            }
            else if (str == "fixed")
            {
                value = Value::fixed;
            }
            else if (str == "tunable")
            {
                value = Value::tunable;
            }
            else if (str == "discrete")
            {
                value = Value::discrete;
            }
            else if (str == "continuous")
            {
                value = Value::continuous;
            }
            else
            {
                value = Value::unknown;
            }
        }

    private:
        Value value;
    };

    class Initial : public IReadWrite
    {
    public:
        enum Value : int
        {
            exact,
            approx,
            calculated,
            unknown
        };

        Initial() = default;
        constexpr Initial(Value value) : value(value) {}

        string to_string() const override
        {
            switch (value)
            {
            case Value::exact:
                return "exact";
            case Value::approx:
                return "approx";
            case Value::calculated:
                return "calculated";
            default:
                return "unknown";
            }
        }

        void from_string(const string &str) override
        {
            if (str == "exact")
            {
                value = Value::exact;
            }
            else if (str == "approx")
            {
                value = Value::approx;
            }
            else if (str == "calculated")
            {
                value = Value::calculated;
            }
            else
            {
                value = Value::unknown;
            }
        }

    private:
        Value value;
    };

    class DependenciesKind : public IReadWrite
    {
    public:
        enum Value : int
        {
            dependent,
            constant,
            fixed,
            tunable,
            discrete
        };

        DependenciesKind() = default;
        constexpr DependenciesKind(Value value) : value(value) {}

        operator Value () const {return value;}

        string to_string() const override
        {
            switch (value)
            {
            case Value::dependent:
                return "dependent";
            case Value::constant:
                return "constant";
            case Value::fixed:
                return "fixed";
            case Value::tunable:
                return "tunable";
            case Value::discrete:
                return "discrete";
            default:
                return "unknown";
            }
        }

        void from_string(const string &str) override
        {
            if (str == "dependent")
            {
                value = Value::dependent;
            }
            else if (str == "constant")
            {
                value = Value::constant;
            }
            else if (str == "fixed")
            {
                value = Value::fixed;
            }
            else if (str == "tunable")
            {
                value = Value::tunable;
            }
            else if (str == "discrete")
            {
                value = Value::discrete;
            }
            else
            {
                value = Value::dependent;
            }
        }

    private:
        Value value;
    };


    class DependenciesKindList : public IList<DependenciesKind>
    {
    };

    class LogCategory : public IReadWrite
    {
    public:
        enum Value : int
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

        LogCategory() = default;
        constexpr LogCategory(Value value) : value(value) {}

        string to_string() const override
        {
            switch (value)
            {
            case Value::logEvents:
                return "logEvents";
            case Value::logSingularLinearSystems:
                return "logSingularLinearSystems";
            case Value::logNonlinearSystems:
                return "logNonlinearSystems";
            case Value::logDynamicStateSelection:
                return "logDynamicStateSelection";
            case Value::logStatusWarning:
                return "logStatusWarning";
            case Value::logStatusDiscard:
                return "logStatusDiscard";
            case Value::logStatusError:
                return "logStatusError";
            case Value::logStatusFatal:
                return "logStatusFatal";
            case Value::logStatusPending:
                return "logStatusPending";
            case Value::logAll:
                return "logAll";
            default:
                return "unknown";
            }
        }

        void from_string(const string &str) override
        {
            if (str == "logEvents")
            {
                value = Value::logEvents;
            }
            else if (str == "logSingularLinearSystems")
            {
                value = Value::logSingularLinearSystems;
            }
            else if (str == "logNonlinearSystems")
            {
                value = Value::logNonlinearSystems;
            }
            else if (str == "logDynamicStateSelection")
            {
                value = Value::logDynamicStateSelection;
            }
            else if (str == "logStatusWarning")
            {
                value = Value::logStatusWarning;
            }
            else if (str == "logStatusDiscard")
            {
                value = Value::logStatusDiscard;
            }
            else if (str == "logStatusError")
            {
                value = Value::logStatusError;
            }
            else if (str == "logStatusFatal")
            {
                value = Value::logStatusFatal;
            }
            else if (str == "logStatusPending")
            {
                value = Value::logStatusPending;
            }
            else if (str == "logAll")
            {
                value = Value::logAll;
            }
            else
            {
                value = Value::logEvents;
            }
        }

    private:
        Value value;
    };

}