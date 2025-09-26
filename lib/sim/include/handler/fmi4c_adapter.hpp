#pragma once

#include "common_log.hpp"

#include <fmi4c.h>

#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <span>
#include <stdexcept>
#include <string>
#include <vector>

namespace ssp4cpp::sim::handler
{
    class FmuInstance
    {
    public:
        common::Logger log = common::Logger("FmuInstance", common::LogLevel::debug);

        FmuInstance(const std::filesystem::path &path, std::string instance_name)
        {
            fmu_path_ = path.string();
            instance_name_ = std::move(instance_name);

            log.debug("[{}] Loading FMU {}", __func__, fmu_path_);
            handle_ = fmi4c_loadFmu(fmu_path_.c_str(), instance_name_.c_str());
            if (handle_ == nullptr)
            {
                auto message = fmi4c_getErrorMessages();
                throw std::runtime_error(std::format("Failed to load FMU '{}': {}", fmu_path_, message ? message : "unknown error"));
            }

            version_ = fmi4c_getFmiVersion(handle_);
            if (version_ != fmiVersion2)
            {
                throw std::runtime_error(std::format("Unsupported FMI version {} for FMU '{}'", static_cast<int>(version_), fmu_path_));
            }
        }

        ~FmuInstance()
        {
            if (handle_ != nullptr)
            {
                log.debug("[{}] Freeing FMU {}", __func__, fmu_path_);
                fmi4c_freeFmu(handle_);
                handle_ = nullptr;
            }
        }

        FmuInstance(const FmuInstance &) = delete;
        FmuInstance &operator=(const FmuInstance &) = delete;

        bool supports_co_simulation() const
        {
            return fmi2_getSupportsCoSimulation(handle_) == true;
        }

        fmiHandle *raw()
        {
            return handle_;
        }

        [[nodiscard]] fmiVersion_t version() const
        {
            return version_;
        }

        [[nodiscard]] const std::string &path() const
        {
            return fmu_path_;
        }

        [[nodiscard]] const std::string &instance_name() const
        {
            return instance_name_;
        }

    private:
        std::string fmu_path_;
        std::string instance_name_;
        fmiHandle *handle_ = nullptr;
        fmiVersion_t version_ = fmiVersionUnknown;
    };

    class CoSimulationModel
    {

    private:
        static bool status_ok(fmi2Status status)
        {
            return status == fmi2OK || status == fmi2Warning;
        }

        FmuInstance &instance_;
        bool instantiated_ = false;
        double current_time_ = 0.0;
        fmi2Status last_status_ = fmi2OK;

    public:
        common::Logger log = common::Logger("CoSimulationModel", common::LogLevel::debug);

        explicit CoSimulationModel(FmuInstance &instance) : instance_(instance)
        {
        }

        ~CoSimulationModel()
        {
            terminate();
        }

        CoSimulationModel(const CoSimulationModel &) = delete;
        CoSimulationModel &operator=(const CoSimulationModel &) = delete;

        bool instantiate(bool visible, bool logging_on)
        {
            if (instantiated_)
            {
                return true;
            }

            if (instance_.version() != fmiVersion2)
            {
                throw std::runtime_error("Only FMI 2.0 FMUs are supported");
            }

            if (!instance_.supports_co_simulation())
            {
                throw std::runtime_error(std::format("FMU '{}' does not support co-simulation", instance_.path()));
            }

            log.debug("[{}] Instantiating FMU {}", __func__, instance_.path());
            auto success = fmi2_instantiate(instance_.raw(),
                                            fmi2CoSimulation,
                                            nullptr,
                                            ::calloc,
                                            ::free,
                                            nullptr,
                                            nullptr,
                                            visible ? fmi2True : fmi2False,
                                            logging_on ? fmi2True : fmi2False);

            instantiated_ = success;
            last_status_ = success ? fmi2OK : fmi2Error;
            current_time_ = 0.0;

            if (!success)
            {
                auto message = fmi4c_getErrorMessages();
                throw std::runtime_error(std::format("Failed to instantiate FMU '{}': {}", instance_.path(), message ? message : "unknown error"));
            }

            return success;
        }

        bool setup_experiment(double start_time, double stop_time, double tolerance)
        {
            if (!instantiated_)
            {
                throw std::logic_error("setup_experiment called before instantiate");
            }

            log.debug("[{}] setup_experiment start:{} stop:{} tolerance:{}", __func__, start_time, stop_time, tolerance);
            auto tolerance_defined = tolerance > 0.0 ? fmi2True : fmi2False;
            auto stop_defined = stop_time > start_time ? fmi2True : fmi2False;

            last_status_ = fmi2_setupExperiment(instance_.raw(), tolerance_defined, tolerance, start_time, stop_defined, stop_time);
            if (status_ok(last_status_))
            {
                current_time_ = start_time;
            }
            return status_ok(last_status_);
        }

        bool enter_initialization_mode()
        {
            if (!instantiated_)
            {
                throw std::logic_error("enter_initialization_mode called before instantiate");
            }

            last_status_ = fmi2_enterInitializationMode(instance_.raw());
            return status_ok(last_status_);
        }

        bool exit_initialization_mode()
        {
            if (!instantiated_)
            {
                throw std::logic_error("exit_initialization_mode called before instantiate");
            }

            last_status_ = fmi2_exitInitializationMode(instance_.raw());
            return status_ok(last_status_);
        }

        bool step(double step_size)
        {
            if (!instantiated_)
            {
                throw std::logic_error("step called before instantiate");
            }

            last_status_ = fmi2_doStep(instance_.raw(), current_time_, step_size, fmi2True);
            if (status_ok(last_status_))
            {
                current_time_ += step_size;
                return true;
            }
            return false;
        }

        bool terminate()
        {
            if (!instantiated_)
            {
                return true;
            }

            log.debug("[{}] Terminating FMU {}", __func__, instance_.path());
            last_status_ = fmi2_terminate(instance_.raw());
            fmi2_freeInstance(instance_.raw());
            instantiated_ = false;
            return status_ok(last_status_);
        }

        [[nodiscard]] double get_simulation_time() const
        {
            return current_time_;
        }

        [[nodiscard]] fmi2Status last_status() const
        {
            return last_status_;
        }

        bool set_real_input_derivative(uint64_t value_reference, int derivative_order, double value)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2Integer order = static_cast<fmi2Integer>(derivative_order);
            fmi2Real data = static_cast<fmi2Real>(value);
            last_status_ = fmi2_setRealInputDerivatives(instance_.raw(), &vr, 1, &order, &data);
            return status_ok(last_status_);
        }

        bool get_real_output_derivative(uint64_t value_reference, int derivative_order, double &out)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2Integer order = static_cast<fmi2Integer>(derivative_order);
            fmi2Real value = 0.0;
            log.warning("[{}]aaa", __func__);
            last_status_ = fmi2_getRealOutputDerivatives(instance_.raw(), &vr, 1, &order, &value);
            log.warning("[{}]aab", __func__);
            if (status_ok(last_status_))
            {
                out = static_cast<double>(value);
                return true;
            }
            return false;
        }

        bool read_real(uint64_t value_reference, double &out)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2Real value = 0.0;
            last_status_ = fmi2_getReal(instance_.raw(), &vr, 1, &value);
            if (status_ok(last_status_))
            {
                out = value;
                return true;
            }
            return false;
        }

        bool read_integer(uint64_t value_reference, int &out)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2Integer value = 0;
            last_status_ = fmi2_getInteger(instance_.raw(), &vr, 1, &value);
            if (status_ok(last_status_))
            {
                out = value;
                return true;
            }
            return false;
        }

        bool read_boolean(uint64_t value_reference, int &out)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2Boolean value = fmi2False;
            last_status_ = fmi2_getBoolean(instance_.raw(), &vr, 1, &value);
            if (status_ok(last_status_))
            {
                out = value;
                return true;
            }
            return false;
        }

        bool write_real(uint64_t value_reference, double value)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2Real data = value;
            last_status_ = fmi2_setReal(instance_.raw(), &vr, 1, &data);
            return status_ok(last_status_);
        }

        bool write_integer(uint64_t value_reference, int value)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2Integer data = value;
            last_status_ = fmi2_setInteger(instance_.raw(), &vr, 1, &data);
            return status_ok(last_status_);
        }

        bool write_boolean(uint64_t value_reference, int value)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2Boolean data = value ? fmi2True : fmi2False;
            last_status_ = fmi2_setBoolean(instance_.raw(), &vr, 1, &data);
            return status_ok(last_status_);
        }

        bool write_string(uint64_t value_reference, const std::string &value)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2String data = value.c_str();
            last_status_ = fmi2_setString(instance_.raw(), &vr, 1, &data);
            return status_ok(last_status_);
        }
    };
}
