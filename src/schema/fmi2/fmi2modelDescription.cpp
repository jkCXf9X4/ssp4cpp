
#include <string>

#include <optional>
#include <vector>

#include "fmi2modelDescription.hpp"
#include "print_misc.hpp"

namespace ssp4cpp::fmi2
{
    // Templates
    template <typename T>
    std::string to_string_optional(const std::optional<T> &opt)
    {
        if (opt)
        {
            return to_string(opt.value()) + "\n";
        }
        else
        {
            return "null\n";
        }
    }

    string to_string(const DefaultExperiment &obj)
    {
        return "DefaultExperiment { \n"
               "startTime: " +
               std::to_string(obj.startTime.value_or(0.0)) +
               "stopTime: " + std::to_string(obj.stopTime.value_or(0.0)) +
               "tolerance: " + std::to_string(obj.tolerance.value_or(0.0)) +
               "stepSize: " + std::to_string(obj.stepSize.value_or(0.0)) +
               " }";
    }

    string to_string(const fmi2ModelDescription &obj)
    {
        // auto default_experiment = defaultExperiment.has_value() ? defaultExperiment.value().to_string() : "null";

        auto default_experiment = to_string_optional(obj.defaultExperiment);

        return "fmi2ModelDescription { \nfmiVersion: " + obj.fmiVersion + "\n" + "modelName: " + obj.modelName + "\n" +
               "DefaultExperiment: " + default_experiment + "\n" + " }";
    }
}
