#pragma once

#include "common_log.hpp"
#include "common_time.hpp"

#include "common_definitions.hpp"

#include <fmi4c.h>

#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <format>
#include <mutex>
#include <span>
#include <stdexcept>
#include <string>
#include <vector>

namespace ssp4cpp::sim::handler
{
    namespace detail
    {
        inline std::once_flag fmi4c_message_flag;
        inline thread_local std::string last_fmi4c_message;

        inline void fmi4c_message_callback(const char *message)
        {
            if (message != nullptr)
            {
                last_fmi4c_message = message;
            }
        }

        inline void ensure_message_callback_registered()
        {
            std::call_once(fmi4c_message_flag, []()
                           { fmi4c_setMessageFunction(&fmi4c_message_callback); });
        }

        inline void clear_last_message()
        {
            last_fmi4c_message.clear();
        }

        inline std::string consume_last_message()
        {
            auto message = last_fmi4c_message;
            last_fmi4c_message.clear();
            return message;
        }
    }

    class FmuInstance
    {
    public:
        common::Logger log = common::Logger("FmuInstance", common::LogLevel::info);

        FmuInstance(const std::filesystem::path &path, std::string instance_name)
        {
            fmu_path_ = path.string();
            instance_name_ = std::move(instance_name);

            log.debug("[{}] Loading FMU {}", __func__, fmu_path_);
            detail::ensure_message_callback_registered();
            detail::clear_last_message();
            handle_ = fmi4c_loadFmu(fmu_path_.c_str(), instance_name_.c_str());
            if (handle_ == nullptr)
            {
                auto message = detail::consume_last_message();
                throw std::runtime_error(std::format("Failed to load FMU '{}': {}", fmu_path_, message.empty() ? "unknown error" : message));
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

        fmuHandle *raw()
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
        fmuHandle *handle_ = nullptr;
        fmiVersion_t version_ = fmiVersionUnknown;
    };

    class CoSimulationModel
    {

    private:
        static bool status_ok(fmi2Status status)
        {
            if (status == fmi2OK)
            {
                return true;
            }

            throw std::runtime_error("Failed status check");
            // return status == fmi2OK; // || status == fmi2Warning;
        }

        FmuInstance &instance_;
        bool instantiated_ = false;
        uint64_t current_time_ = 0;
        fmi2Status last_status_ = fmi2OK;

    public:
        common::Logger log = common::Logger("CoSimulationModel", common::LogLevel::info);

        explicit CoSimulationModel(FmuInstance &instance) : instance_(instance)
        {
        }

        ~CoSimulationModel()
        {
            terminate();
        }

        CoSimulationModel(const CoSimulationModel &) = delete;
        CoSimulationModel &operator=(const CoSimulationModel &) = delete;

        fmi2InstanceHandle *handle;

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
            detail::ensure_message_callback_registered();
            detail::clear_last_message();
            handle = fmi2_instantiate(instance_.raw(),
                                      fmi2CoSimulation,
                                      nullptr,
                                      ::calloc,
                                      ::free,
                                      nullptr,
                                      nullptr,
                                      visible ? fmi2True : fmi2False,
                                      logging_on ? fmi2True : fmi2False);

            bool success = handle != nullptr;
            instantiated_ = success;
            last_status_ = success ? fmi2OK : fmi2Error;
            current_time_ = 0;

            if (!success)
            {
                auto message = detail::consume_last_message();
                throw std::runtime_error(std::format("Failed to instantiate FMU '{}': {}", instance_.path(), message.empty() ? "unknown error" : message));
            }

            return success;
        }

        bool setup_experiment(uint64_t start_time, uint64_t stop_time, double tolerance)
        {
            if (!instantiated_)
            {
                throw std::logic_error("setup_experiment called before instantiate");
            }

            // if start is close to 0, set it to zero
            if (start_time < 1000)
            {
                start_time = 0;
            }
            
            auto stop_defined = stop_time > start_time ? fmi2True : fmi2False;
            auto tolerance_defined = tolerance > 0.0 ? fmi2True : fmi2False;

            double start = common::time::ns_to_s (start_time);
            double stop = common::time::ns_to_s (stop_time);

            log.debug("[{}] setup_experiment start:{} stop:{} tolerance:{}", __func__, start, stop, tolerance);

            last_status_ = fmi2_setupExperiment(handle, tolerance_defined, tolerance, start, stop_defined, stop);
            if (status_ok(last_status_))
            {
                current_time_ = start_time;
                log.info("[{}] start:{}", __func__, current_time_);
            }
            return status_ok(last_status_);
        }

        bool enter_initialization_mode()
        {
            if (!instantiated_)
            {
                throw std::logic_error("enter_initialization_mode called before instantiate");
            }

            last_status_ = fmi2_enterInitializationMode(handle);
            return status_ok(last_status_);
        }

        bool exit_initialization_mode()
        {
            if (!instantiated_)
            {
                throw std::logic_error("exit_initialization_mode called before instantiate");
            }

            last_status_ = fmi2_exitInitializationMode(handle);
            return status_ok(last_status_);
        }

        uint64_t step_until(uint64_t stop_time)
        {
            auto sim_time = get_simulation_time();
            while (sim_time < stop_time)
            {
                auto step_time = stop_time - sim_time;

                IF_LOG({
                    log.debug("[{}] step_time {}s ", __func__, common::time::ns_to_s(step_time));
                });

                if (this->step(step_time) == false)
                {
                    int status = last_status();
                    log.error("Error! step() returned with status: {}", std::to_string(status));
                    if (status == 3)
                    {
                        throw std::runtime_error("Execution failed");
                    }
                }
                sim_time = get_simulation_time();

                IF_LOG({
                    log.trace("[{}], sim time {}", __func__, sim_time);
                });
            }
            return sim_time;
        }

        bool step(uint64_t step_size)
        {
            if (!instantiated_)
            {
                throw std::logic_error("step called before instantiate");
            }

            double current = common::time::ns_to_s(current_time_);
            double step = common::time::ns_to_s(step_size);

            IF_LOG({
                log.debug("[{}] current {} step {}", __func__, current, step);
            });

            last_status_ = fmi2_doStep(handle, current, step, fmi2True);
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
            last_status_ = fmi2_terminate(handle);
            fmi2_freeInstance(handle);
            instantiated_ = false;
            return status_ok(last_status_);
        }

        [[nodiscard]] uint64_t get_simulation_time() const
        {
            return current_time_;
        }

        [[nodiscard]] fmi2Status last_status() const
        {
            return last_status_;
        }

        // Its important that the input type corresponds to the same fmi2 type, else there must be a cast

        bool set_real_input_derivative(uint64_t value_reference, int derivative_order, double value)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2Integer order = static_cast<fmi2Integer>(derivative_order);
            last_status_ = fmi2_setRealInputDerivatives(handle, &vr, 1, &order, &value);
            return status_ok(last_status_);
        }

        bool get_real_output_derivative(uint64_t value_reference, int derivative_order, double &out)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2Integer order = static_cast<fmi2Integer>(derivative_order);
            last_status_ = fmi2_getRealOutputDerivatives(handle, &vr, 1, &order, &out);
            return status_ok(last_status_);
        }

        bool read_real(uint64_t value_reference, double &out)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            last_status_ = fmi2_getReal(handle, &vr, 1, &out);
            return status_ok(last_status_);
        }

        bool read_integer(uint64_t value_reference, int &out)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            last_status_ = fmi2_getInteger(handle, &vr, 1, &out);
            return status_ok(last_status_);
        }

        bool read_boolean(uint64_t value_reference, int &out)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            last_status_ = fmi2_getBoolean(handle, &vr, 1, &out);
            return status_ok(last_status_);
        }

        bool read_string(uint64_t value_reference, std::string &out)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2String value = 0;
            last_status_ = fmi2_getString(handle, &vr, 1, &value);
            if (status_ok(last_status_))
            {
                out = std::string(value);
                return true;
            }
            return false;
        }

        bool write_real(uint64_t value_reference, double value)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            last_status_ = fmi2_setReal(handle, &vr, 1, &value);

            // There must be a read after the last write for some fmus...
            // Or there is a solver restart
            // can be seen as an event
            fmi2Real data = 0.0;
            fmi2_getReal(handle, &vr, 1, &data);
            return status_ok(last_status_);
        }

        bool write_integer(uint64_t value_reference, int value)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            last_status_ = fmi2_setInteger(handle, &vr, 1, &value);
            return status_ok(last_status_);
        }

        bool write_boolean(uint64_t value_reference, int value)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            last_status_ = fmi2_setBoolean(handle, &vr, 1, &value);
            return status_ok(last_status_);
        }

        bool write_string(uint64_t value_reference, const std::string &value)
        {
            fmi2ValueReference vr = static_cast<fmi2ValueReference>(value_reference);
            fmi2String data = value.c_str();
            last_status_ = fmi2_setString(handle, &vr, 1, &data);
            return status_ok(last_status_);
        }
    };
}
