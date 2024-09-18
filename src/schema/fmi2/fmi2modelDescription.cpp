
#include <string>

#include <optional>
#include <vector>
#include "node_base.hpp"

#include "fmi2modelDescription.hpp"
#include "print_misc.hpp"

namespace ssp4cpp::fmi2
{
    Templates
    template <typename T>
    std::string to_string_optional(const std::optional<T> &opt)
    {
        if (opt)
        {
            return opt.value().to_string() + "\n";
        }
        else
        {
            return "null\n";
        }
    }

    string DefaultExperiment::to_string()
    {
        return "DefaultExperiment { \n"
               "startTime: " +
               std::to_string(startTime.value_or(0.0)) +
               "stopTime: " + std::to_string(stopTime.value_or(0.0)) +
               "tolerance: " + std::to_string(tolerance.value_or(0.0)) +
               "stepSize: " + std::to_string(stepSize.value_or(0.0)) +
               " }";
    }

    string fmi2ModelDescription::to_string()
    {
        // auto default_experiment = defaultExperiment.has_value() ? defaultExperiment.value().to_string() : "null";

        auto default_experiment = to_string_optional(defaultExperiment)

        return "fmi2ModelDescription { \nfmiVersion: " + fmiVersion + "\n" + "modelName: " + modelName + "\n" +
               "DefaultExperiment: " + default_experiment + "\n" + " }";
    }
}
