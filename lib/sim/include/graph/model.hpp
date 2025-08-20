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

    struct ConnectorInfo
    {
        utils::DataType type;
        size_t size;
        std::string name; // for debug

        uint32_t index;
        uint64_t value_ref;

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

        /** @brief Convert to string for debugging purposes. */
        std::string to_string()
        {
            return common::str::stream_to_str(*this);
        }
    };

    struct ConnectionInfo
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

                /** @brief Convert to string for debugging purposes. */
        std::string to_string()
        {
            return common::str::stream_to_str(*this);
        }
    };

    class Model : public common::graph::Node
    {
        uint64_t delay = 0;
        uint64_t start_time = 0;
        uint64_t end_time = 0;
        uint64_t delayed_time = 0;

    public:
        common::Logger log = common::Logger("Model", common::LogLevel::info);

        handler::FmuInfo *fmu;

        unique_ptr<utils::RingStorage> input_area;
        unique_ptr<utils::RingStorage> output_area;

        std::map<std::string, ConnectorInfo> inputs;
        std::map<std::string, ConnectorInfo> outputs;
        vector<ConnectionInfo> connections;

        Model(std::string name, handler::FmuInfo *fmu)
        {
            this->fmu = fmu;
            this->name = name;
            input_area = make_unique<utils::RingStorage>(3);
            output_area = make_unique<utils::RingStorage>(5);
        }

        ~Model()
        {
            log.ext_trace("[{}] Destroying Model", __func__);
        }

        friend ostream &operator<<(ostream &os, const Model &obj)
        {
            os << "Model { \n"
               << "Name: " << obj.name << endl
               << " }" << endl;

            return os;
        }

                /** @brief Convert to string for debugging purposes. */
        std::string to_string()
        {
            return common::str::stream_to_str(*this);
        }

        // Retrieve inputs, and prepare the model
        void pre(uint64_t time)
        {
            log.ext_trace("[{}] Init", __func__);

            auto area = input_area->push(time);
            // Fetch valid data to input area
            for (auto &connection : connections)
            {
                auto output_item = connection.source_storage->get_valid_item(time, connection.source_index);
                if (output_item)
                {
                    auto input_item = input_area->get_item(area, connection.target_index);
                    // fib input data
                    memcpy(input_item, output_item, connection.size);
                }
            }
            input_area->flag_new_data(area);

            for (auto &[_, input] : inputs)
            {
                auto input_item = input_area->get_item(area, input.index);
                utils::write_to_model_(input.type, *fmu->model, input.value_ref, input_item);
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
            for (auto &[_, output] : outputs)
            {
                auto item = output_area->get_item(area, output.index);
                utils::read_from_model_(output.type, *fmu->model, output.value_ref, (void *)item);
                // fib output data
            }
            output_area->flag_new_data(area);
        }

        uint64_t invoke(uint64_t time)
        {
            start_time = end_time;
            end_time = time;
            auto timestep = end_time - start_time;
            delayed_time = end_time - delay;

            log.trace("[{}] {} start_time: {} timestep: {} end_time: {}, delayed_time {}",
                      __func__, this->name.c_str(), start_time, timestep, end_time, delayed_time);

            pre(start_time);

            take_step(timestep);
            // this should return the new endtime if we have early return

            post(delayed_time);

            return delayed_time;
        }
    };
}