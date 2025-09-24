#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "FMI2_Enums_Ext.hpp"

#include "data_ring_storage.hpp"
#include "data_recorder.hpp"
#include "invocable.hpp"

#include "fmu_handler.hpp"

#include <string>
#include <vector>
#include <functional>

namespace ssp4cpp::sim::graph
{
    // forward declaration
    class FmuModel;

    struct ConnectorInfo : public common::str::IString
    {
        utils::DataType type;
        size_t size;
        std::string name; // for debug

        uint32_t index;
        uint64_t value_ref;

        std::unique_ptr<std::byte[]> initial_value;

        virtual void print(std::ostream &os) const
        {
            os << "ConnectorInfo { "
               << "name: " << name
               << ", type: " << type
               << ", size: " << size
               << ", index: " << index
               << ", value_ref: " << value_ref
               << " }";
        }
    };

    struct ConnectionInfo : public common::str::IString
    {
        utils::DataType type;
        size_t size;

        utils::RingStorage *source_storage;
        utils::RingStorage *target_storage;
        uint32_t source_index;
        uint32_t target_index;

        virtual void print(std::ostream &os) const
        {
            os << "ConnectionInfo { "
               << "type: " << type
               << ", size: " << size
               << ", source_storage: " << source_storage
               << ", target_storage: " << target_storage
               << ", source_index: " << source_index
               << ", target_index: " << target_index
               << " }";
        }
    };

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

                    auto data_type_str = fmi2::ext::enums::data_type_to_string(input.type, data_ptr);
                    log.debug("[{}] Set initial input value for {}, {} : {}",
                              __func__, name, input.type.to_string(), data_type_str);

                    // set input area to reflect the data to ensure that next iteration correct data will be used
                    if (input.type != DataType::string)
                    {
                        auto item = input_area->get_item(area, input.index);
                        memcpy(item, data_ptr, input.size);
                    }
                    else
                    {
                        log.warning("[{}] Input area does not support initial value for strings yet", __func__);
                    }
                }
            }
            input_area->flag_new_data(area);
            recorder->update();

            log.debug("[{}] Input area after initialization: {}", __func__, input_area->data->export_area(area));
        }

        // @todo: cleanup needed of printouts and initialization of start values

        void init()
        {
            log.trace("[{}] FmuModel init {}", __func__, name);

            log.debug("[{}] setup_experiment: {} ", __func__, name);
            if (!fmu->model->setup_experiment(0, 10000, 1e-4))
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

        // hot path
        void pre(uint64_t model_start_time, uint64_t valid_input_time)
        {

            auto area = input_area->push(model_start_time);
#ifndef NDEBUG
            log.trace("[{}] Init, Retrieve inputs, and prepare the model", __func__);
            log.ext_trace("[{}] Fetch valid data to input area. Area {}", __func__, area);

            log.trace("[{}] Copy connections", __func__);
#endif
            for (auto &connection : connections)
            {
#ifndef NDEBUG
                log.ext_trace("[{}] Fetch valid data connection {}", __func__, connection.to_string());
#endif
                auto output_item = connection.source_storage->get_valid_item(valid_input_time, connection.source_index);
                if (output_item)
                {
#ifndef NDEBUG
                    auto data_type_str = fmi2::ext::enums::data_type_to_string(connection.type, output_item);
                    log.debug("[{}] Found valid item, copying data to storage area: {}",
                              __func__, data_type_str);
#endif

                    auto input_item = input_area->get_item(area, connection.target_index);
                    memcpy(input_item, output_item, connection.size);
                }
            }
            input_area->flag_new_data(area);
            recorder->update();

#ifndef NDEBUG
            log.trace("[{}] Copy data to model", __func__);
#endif
            for (auto &[_, input] : inputs)
            {
                auto input_item = input_area->get_item(area, input.index);

#ifndef NDEBUG
                auto data_type_str = fmi2::ext::enums::data_type_to_string(input.type, input_item);
                log.debug("[{}] Copying input to model. {}, data: {}", __func__, input.to_string(), data_type_str);
#endif

                utils::write_to_model_(input.type, *fmu->model, input.value_ref, (void *)input_item);
            }
#ifndef NDEBUG
            log.debug("[{}] Input area after pre: {}", __func__, input_area->data->export_area(area));
#endif
        }

        // hot path
        void take_step(uint64_t timestep)
        {
            auto step_double = (double)timestep / common::time::nanoseconds_per_second;
#ifndef NDEBUG
            log.debug("[{}] FmuModel {} ", __func__, step_double);
            auto model_timer = common::time::Timer();
#endif

            if (fmu->model->step(step_double) == false)
            {
                int status = (int)fmu->model->last_status();
                log.error("Error! step() returned with status: {}", std::to_string(status));
                if (status == 3)
                {
                    throw std::runtime_error("Execution failed");
                }
            }

#ifndef NDEBUG
            this->invocation_walltime_ns += model_timer.stop();
            log.trace("[{}], sim time {}", __func__, fmu->model->get_simulation_time());
#endif
        }

        // hot path
        void post(uint64_t time)
        {
#ifndef NDEBUG
            log.ext_trace("[{}] Init {}", __func__, time);
            log.trace("[{}] Copy data from model", __func__);
#endif

            auto area = output_area->push(time);
            for (auto &[_, output] : outputs)
            {
#ifndef NDEBUG
                log.ext_trace("[{}] Copying ref {} ({}) to index {}", __func__, output.value_ref, output.type.to_string(), output.index);
#endif

                auto item = output_area->get_item(area, output.index);
                utils::read_from_model_(output.type, *fmu->model, output.value_ref, (void *)item);
                // fib output data
            }
            output_area->flag_new_data(area);
            recorder->update();
#ifndef NDEBUG
            log.trace("[{}] Completed copy from model", __func__);
            log.debug("[{}] Output area after post: {}", __func__, output_area->data->export_area(area));
#endif
        }

        // hot path
        uint64_t invoke(StepData step_data) override final
        {
#ifndef NDEBUG
            log.debug("[{}] Init {}, stepdata: {}", __func__, name, step_data.to_string());
#endif

            _start_time = _end_time;
            _end_time = step_data.end_time;
            auto _timestep = _end_time - _start_time;

            auto delayed_time = _end_time - delay;
#ifndef NDEBUG
            log.trace("[{}] {} start_time: {} valid_input_time: {} timestep: {} end_time: {}, delayed_time {}",
                      __func__, this->name.c_str(), _start_time, step_data.valid_input_time, _timestep, _end_time, delayed_time);
#endif

            pre(_start_time, step_data.valid_input_time);

            take_step(_timestep);
            // this should return the new endtime if we have early return

            post(delayed_time);
#ifndef NDEBUG
            log.ext_trace("[{}] Completed", __func__, step_data.to_string());
#endif
            return delayed_time;
        }
    };
}