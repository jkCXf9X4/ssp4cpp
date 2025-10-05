#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "common_definitions.hpp"

#include "FMI2_Enums_Ext.hpp"

#include "data_ring_storage.hpp"
#include "data_recorder.hpp"
#include "invocable.hpp"
#include "config.hpp"

#include "fmu_handler.hpp"
#include "model_connection.hpp"
#include "model_connector.hpp"

#include <string>
#include <vector>
#include <functional>

namespace ssp4cpp::sim::graph
{

    class FmuModel final : public Invocable
    {
        uint64_t delay = 0;
        uint64_t _start_time = 0;
        uint64_t _end_time = 0;

    public:
        common::Logger log = common::Logger("FmuModel", common::LogLevel::info);

        handler::FmuInfo *fmu;

        std::unique_ptr<utils::RingStorage> input_area;
        std::unique_ptr<utils::RingStorage> output_area;
        utils::DataRecorder *recorder;

        std::map<std::string, ConnectorInfo> inputs;
        std::map<std::string, ConnectorInfo> outputs;
        std::map<std::string, ConnectorInfo> parameters;
        std::vector<ConnectionInfo> connections;

        bool forward_derivatives = utils::Config::getOr<bool>("simulation.forward_derivatives", true);

        FmuModel(std::string name, handler::FmuInfo *fmu)
        {
            this->fmu = fmu;
            this->name = name;
            input_area = make_unique<utils::RingStorage>(2, name + ".input");
            output_area = make_unique<utils::RingStorage>(10, name + ".output");
        }

        ~FmuModel()
        {
            log.ext_trace("[{}] Destroying FmuModel", __func__);
            fmu->model->terminate();
        }

        virtual void print(std::ostream &os) const
        {
            os << "FmuModel { \n"
               << "Name: " << name
               << "\n}\n";
        }

        void set_start_values(std::map<std::string, ConnectorInfo> &connectors)
        {
            for (auto &[name, connector] : connectors)
            {
                if (connector.initial_value)
                {
                    auto data_ptr = (void *)connector.initial_value.get();

                    auto data_type_str = fmi2::ext::enums::data_type_to_string(connector.type, data_ptr);
                    log.debug("[{}] Set initial value for {}, {} : {}",
                              __func__, name, connector.type.to_string(), data_type_str);

                    utils::write_to_model_(connector.type, *fmu->model, connector.value_ref, data_ptr);
                }
            }
        }

        void set_initial_input_area(std::map<std::string, ConnectorInfo> &in)
        {
            log.trace("[{}] Set input start area", __func__);
            auto area = input_area->push(0); //
            for (auto &[name, input] : in)
            {
                if (input.initial_value)
                {
                    auto data_ptr = (void *)input.initial_value.get();
                    auto item = input_area->get_item(area, input.index);

                    auto data_type_str = fmi2::ext::enums::data_type_to_string(input.type, data_ptr);
                    log.debug("[{}] Set initial input value for {}, {} : {}",
                              __func__, name, input.type.to_string(), data_type_str);

                    // set input area to reflect the data to ensure that next iteration correct data will be used
                    if (input.type == DataType::string)
                    {
                        // Move the internal string rep, not the std::string itself
                        *(std::string *)item = *(std::string *)data_ptr;
                    }
                    else
                    {
                        memcpy(item, data_ptr, input.size);
                    }
                }
            }
            input_area->flag_new_data(area);
            recorder->update();

            log.debug("[{}] Input area after initialization: {}", __func__, input_area->data->export_area(area));
        }

        void init()
        {
            log.trace("[{}] FmuModel init {}", __func__, name);

            double start_time = utils::Config::get<double>("simulation.start_time");
            double end_time = utils::Config::get<double>("simulation.stop_time") + 10;
            double tolerance = utils::Config::get<double>("simulation.tolerance");

            log.debug("[{}] setup_experiment: {} ", __func__, name);
            if (!fmu->model->setup_experiment(start_time, end_time, tolerance))
                log.error("[{}] setup_experiment failed ", __func__);

            log.debug("[{}] enter_initialization_mode: {} ", __func__, name);
            if (!fmu->model->enter_initialization_mode())
            {
                log.error("[{}] enter_initialization_mode failed ", __func__);
                throw std::runtime_error(std::format("[{}] enter_initialization_mode failed for {}", __func__, name));
            }

            log.trace("[{}] Set start parameter values", __func__);
            set_start_values(this->parameters);

            log.debug("[{}] exit_initialization_mode: {} ", __func__, name);
            if (!fmu->model->exit_initialization_mode())
            {
                log.error("[{}] exit_initialization_mode failed ", __func__);
                throw std::runtime_error(std::format("[{}] exit_initialization_mode failed for {}", __func__, name));
            }

            log.ext_trace("[{}] Set input area", __func__);
            set_initial_input_area(this->inputs);

            log.ext_trace("[{}] Invoke at timestep 0", __func__);
            invoke(StepData(0, 0, 0));

            log.ext_trace("[{}] FmuModel init completed", __func__);
        }

        inline void retrieve_model_inputs(int target_area, uint64_t valid_input_time)
        {
            IF_LOG({
                log.ext_trace("[{}] Area {}", __func__, target_area);
                log.trace("[{}] Copy connections", __func__);
            });

            for (auto &connection : connections)
            {
                IF_LOG({
                    log.ext_trace("[{}] Fetch valid data connection {}", __func__, connection.to_string());
                });

                auto source_area = connection.source_storage->get_valid_area(valid_input_time);
                if (source_area != -1)
                {
                    auto source_item = connection.source_storage->get_item(source_area, connection.source_index);
                    IF_LOG({
                        auto data_type_str = fmi2::ext::enums::data_type_to_string(connection.type, source_item);
                        log.debug("[{}] Found valid item, copying data to target area: {}",
                                  __func__, data_type_str);
                    });

                    auto target_item = input_area->get_item(target_area, connection.target_index);
                    memcpy(target_item, source_item, connection.size);

                    if (forward_derivatives && connection.forward_derivatives)
                    {
                        IF_LOG({
                            log.ext_trace("[{}] Copying derivatives {}", __func__, connection.to_string());
                        });

                        for (int order = 1; order <= connection.forward_derivatives_order; ++order)
                        {
                            auto source_der = connection.source_storage->get_derivative(source_area, connection.source_index, order);
                            auto target_der = connection.target_storage->get_derivative(target_area, connection.target_index, order);
                            IF_LOG({
                                log.ext_trace("[{}] Copying derivatives {} -> {}", __func__, (uint64_t)source_der, (uint64_t)target_der);
                            });

                            memcpy(target_der, source_der, sizeof(double));
                        }
                    }
                }
            }
        }

        inline void write_data_to_model(int target_area)
        {
            IF_LOG({
                log.trace("[{}] Write data to model", __func__);
            });

            for (auto &[_, input] : inputs)
            {
                auto input_item = input_area->get_item(target_area, input.index);

                IF_LOG({
                    auto data_type_str = fmi2::ext::enums::data_type_to_string(input.type, input_item);
                    log.debug("[{}] Copying input to model. {}, data: {}", __func__, input.to_string(), data_type_str);
                });

                utils::write_to_model_(input.type, *fmu->model, input.value_ref, (void *)input_item);
            }
        }

        // hot path
        void pre(uint64_t model_start_time, uint64_t valid_input_time)
        {
            IF_LOG({
                log.ext_trace("[{}] Init", __func__);
            });

            auto target_area = input_area->push(model_start_time);

            retrieve_model_inputs(target_area, valid_input_time);

            input_area->flag_new_data(target_area);

            write_data_to_model(target_area);

            if (forward_derivatives)
            {
                apply_input_derivatives(target_area);
            }

            IF_LOG({
                log.debug("[{}] Input area after pre: {}", __func__, input_area->data->export_area(target_area));
            });
        }

        inline void read_values_from_model(int area)
        {
            IF_LOG({
                log.trace("[{}] Init, area {}", __func__, area);
            });

            for (auto &[_, output] : outputs)
            {
                auto item = output_area->get_item(area, output.index);
                IF_LOG({
                    log.ext_trace("[{}] Copying ref {} ({}) to index {} ", __func__, output.value_ref, output.type.to_string(), output.index, (int64_t)item);
                });

                utils::read_from_model_(output.type, *fmu->model, output.value_ref, (void *)item);
            }
            IF_LOG({
                log.trace("[{}] Completed copy from model", __func__);
            });
        }

        // hot path
        void post(uint64_t time)
        {
            IF_LOG({
                log.ext_trace("[{}] Init {}", __func__, time);
            });

            auto area = output_area->push(time);

            read_values_from_model(area);

            if (forward_derivatives)
            {
                fetch_output_derivatives(area);
            }
            output_area->flag_new_data(area);
            recorder->update();
            IF_LOG({
                log.debug("[{}] Output area after post: {}", __func__, output_area->data->export_area(area));
            });
        }

        // hot path
        uint64_t invoke(StepData step_data) override final
        {
            IF_LOG({
                log.debug("[{}] Init {}, stepdata: {}", __func__, name, step_data.to_string());
            });

            _start_time = _end_time;
            _end_time = step_data.end_time;
            auto _timestep = _end_time - _start_time;

            IF_LOG({
                log.trace("[{}] {} start_time: {} valid_input_time: {} timestep: {} end_time: {}",
                          __func__, this->name.c_str(), _start_time, step_data.valid_input_time, _timestep, _end_time);
            });

            pre(_start_time, step_data.valid_input_time);

            _end_time = fmu->model->step_until(_end_time);

            auto delayed_time = _end_time - delay;
            post(delayed_time);
            IF_LOG({
                log.ext_trace("[{}] Completed, delayed_time:", __func__, delayed_time);
            });

            return delayed_time;
        }

        inline void apply_input_derivatives(std::size_t area)
        {
            IF_LOG({
                log.trace("[{}] Init area {} ", __func__, area);
            });

            auto model_timer = common::time::Timer();
            for (auto &[_, connector] : inputs)
            {
                if (!connector.forward_derivatives)
                {
                    continue;
                }

                for (int order = 1; order <= connector.forward_derivatives_order; ++order)
                {
                    auto der_ptr = input_area->get_derivative(area, connector.index, order);
                    if (der_ptr == nullptr)
                    {
                        continue;
                    }

                    double value = *reinterpret_cast<double *>(der_ptr);
                    if (!fmu->model->set_real_input_derivative(connector.value_ref, order, value))
                    {
                        log.warning("[{}] Failed to set input derivative order {} for {} (status {})",
                                    __func__,
                                    order,
                                    connector.name,
                                    static_cast<int>(fmu->model->last_status()));
                    }
                }
            }
            this->walltime_ns += model_timer.stop();
        }

        inline void fetch_output_derivatives(std::size_t area)
        {
            IF_LOG({
                log.trace("[{}] Init area {} ", __func__, area);
            });

            auto model_timer = common::time::Timer();

            for (auto &[_, connector] : outputs)
            {
                // dont run at time 0.0
                if (!connector.forward_derivatives || _end_time == 0)
                {
                    continue;
                }

                for (int order = 1; order <= connector.forward_derivatives_order; ++order)
                {
                    IF_LOG({
                        log.trace("[{}] get_derivative position for vr:{} name: {} order: {}", __func__, connector.value_ref, connector.name, order);
                    });

                    auto der_ptr = output_area->get_derivative(area, connector.index, order);
                    if (der_ptr == nullptr)
                    {
                        log.warning("[{}] Failed to find derivate item for {}", __func__, connector.name);
                        continue;
                    }
                    IF_LOG({
                        log.trace("[{}] get_derivative for {} ", __func__, connector.name);
                    });

                    double value = 0.0;
                    if (!fmu->model->get_real_output_derivative(connector.value_ref, order, value))
                    {
                        log.warning("[{}] Failed to get output derivative order {} for {} (status {})",
                                    __func__,
                                    order,
                                    connector.name,
                                    static_cast<int>(fmu->model->last_status()));
                        continue;
                    }
                    IF_LOG({
                        log.trace("[{}] storing derivate for {} ", __func__, connector.name);
                    });

                    *reinterpret_cast<double *>(der_ptr) = value;
                }
            }
            this->walltime_ns += model_timer.stop();
        }
    };
}
