#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "data_ring_storage.hpp"

#include "fmu_handler.hpp"

#include <string>
#include <vector>
#include <functional>

namespace ssp4cpp::sim::graph
{
    // forward declaration
    class Model;

    struct ConnectorInfo : public common::str::IString
    {
        utils::DataType type;
        size_t size;
        std::string name; // for debug

        uint32_t index;
        uint64_t value_ref;

        std::unique_ptr<std::byte[]> initial_value;

        friend std::ostream &operator<<(std::ostream &os, const ConnectorInfo &obj)
        {
            os << "ConnectorInfo { "
               << "name: " << obj.name
               << ", type: " << obj.type
               << ", size: " << obj.size
               << ", index: " << obj.index
               << ", value_ref: " << obj.value_ref
               << " }";
            return os;
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

        friend std::ostream &operator<<(std::ostream &os, const ConnectionInfo &obj)
        {
            os << "ConnectionInfo { "
               << "type: " << obj.type
               << ", size: " << obj.size
               << ", source_storage: " << obj.source_storage
               << ", target_storage: " << obj.target_storage
               << ", source_index: " << obj.source_index
               << ", target_index: " << obj.target_index
               << " }";
            return os;
        }
    };

    class Model final : public common::graph::Node
    {
        uint64_t delay = 0;
        uint64_t _start_time = 0;
        uint64_t _end_time = 0;

    public:
        common::Logger log = common::Logger("Model", common::LogLevel::debug);

        handler::FmuInfo *fmu;

        std::unique_ptr<utils::RingStorage> input_area;
        std::unique_ptr<utils::RingStorage> output_area;
        utils::DataRecorder *recorder;

        std::map<std::string, ConnectorInfo> inputs;
        std::map<std::string, ConnectorInfo> outputs;
        std::map<std::string, ConnectorInfo> parameters;
        vector<ConnectionInfo> connections;

        Model(std::string name, handler::FmuInfo *fmu)
        {
            this->fmu = fmu;
            this->name = name;
            input_area = make_unique<utils::RingStorage>(3, name + ".input");
            output_area = make_unique<utils::RingStorage>(5, name + ".output");
        }

        ~Model()
        {
            log.ext_trace("[{}] Destroying Model", __func__);
            fmu->model->terminate();
        }

        friend ostream &operator<<(ostream &os, const Model &obj)
        {
            os << "Model { \n"
               << "Name: " << obj.name << endl
               << " }" << endl;

            return os;
        }

        void init()
        {
            log.trace("[{}] Model init ", __func__);

            // set parameters
            for (auto &[name, parameter] : this->parameters)
            {
                if (parameter.initial_value)
                {
                    log.ext_trace("[{}] Set initial value for {}", __func__, name);
                    utils::write_to_model_(parameter.type, *fmu->model, parameter.value_ref, (void *)parameter.initial_value.get());
                }
            }

            fmu->model->setup_experiment();
            fmu->model->enter_initialization_mode();
            fmu->model->exit_initialization_mode();

            log.ext_trace("[{}] Model init completed", __func__);
        }

        // Retrieve inputs, and prepare the model
        void pre(uint64_t model_start_time, uint64_t valid_input_time)
        {
            log.trace("[{}] Init", __func__);

            if (input_area->data->items == 0)
            {
                return;
            }

            auto area = input_area->push(model_start_time);
            log.ext_trace("[{}] Area {}", __func__, area);
            // Fetch valid data to input area
            // fib input data if needed
            log.trace("[{}] Copy connections", __func__);
            for (auto &connection : connections)
            {
                log.ext_trace("[{}] Fetch valid data connection {}", __func__, connection.to_string());
                auto output_item = connection.source_storage->get_valid_item(valid_input_time, connection.source_index);
                if (output_item)
                {
                    log.ext_trace("[{}] Found valid item, copying data", __func__);
                    auto input_item = input_area->get_item(area, connection.target_index);
                    memcpy(input_item, output_item, connection.size);
                }
            }
            input_area->flag_new_data(area);
            recorder->update();

            log.trace("[{}] Copy data to model", __func__);
            for (auto &[_, input] : inputs)
            {
                log.ext_trace("[{}] Copying input {}", __func__, input.to_string());
                auto input_item = input_area->get_item(area, input.index);
                utils::write_to_model_(input.type, *fmu->model, input.value_ref, (void *)input_item);
            }
        }

        void take_step(uint64_t timestep)
        {
            auto step_double = (double)timestep / common::time::nanoseconds_per_second;
            log.trace("[{}] Model {} ", __func__, step_double);
            if (fmu->model->step(step_double) == false)
            {
                int status = (int)fmu->model->last_status();
                log.error("Error! step() returned with status: {}", std::to_string(status));
                if (status == 3)
                {
                    throw runtime_error("Execution failed");
                }
            }
            log.trace("[{}], sim time {}", __func__, fmu->model->get_simulation_time());
        }

        void post(uint64_t time)
        {
            log.ext_trace("[{}] Init", __func__);

            auto area = output_area->push(time);
            log.trace("[{}] Copy data from model", __func__);
            for (auto &[_, output] : outputs)
            {
                auto item = output_area->get_item(area, output.index);
                utils::read_from_model_(output.type, *fmu->model, output.value_ref, (void *)item);
                // fib output data
            }
            output_area->flag_new_data(area);
            recorder->update();
        }

        uint64_t invoke(uint64_t start_time, uint64_t end_time, uint64_t timestep, uint64_t valid_input_time)
        {
            _start_time = _end_time;
            _end_time = end_time;
            auto _timestep = _end_time - _start_time;

            auto delayed_time = _end_time - delay;

            log.trace("[{}] {} start_time: {} valid_input_time: {} timestep: {} end_time: {}, delayed_time {}",
                      __func__, this->name.c_str(), _start_time, valid_input_time, _timestep, _end_time, delayed_time);

            pre(_start_time, valid_input_time);

            take_step(_timestep);
            // this should return the new endtime if we have early return

            post(delayed_time);

            return delayed_time;
        }
    };
}