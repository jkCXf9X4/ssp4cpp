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

    struct InputInfo
    {
        utils::DataType type;
        size_t size;
        std::string name; // for debug

        utils::RingStorage *output_storage;
        uint32_t output_index;

        uint32_t input_index;
        uint64_t input_value_ref;
    };

    struct OutputInfo
    {
        utils::DataType type;
        size_t size;
        std::string name;

        uint32_t output_index;
        uint64_t output_value_ref;
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

        vector<InputInfo> inputs;
        vector<OutputInfo> outputs;

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

        // Retrieve inputs, and prepare the model
        void pre(uint64_t time)
        {
            log.ext_trace("[{}] Init", __func__);

            auto area = input_area->push(time);
            for (auto &in : inputs)
            {
                auto output_item = in.output_storage->get_valid_item(time, in.output_index);
                
                void* input_item;
                if (true) // store the input data before use
                {
                    input_item = input_area->get_item(area, in.input_index);
                    memcpy(input_item, output_item, in.size);
                }
                else // use the output data directly
                {
                    input_item = output_item;
                }

                utils::write_to_model_(in.type, *fmu->model, in.input_value_ref, input_item);
            }
            input_area->flag_new_data(area);
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
            for (auto out : outputs)
            {
                auto item = output_area->get_item(area, out.output_index);

                utils::read_from_model_(out.type, *fmu->model, out.output_value_ref, (void *)item);
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

            // post(delayed_time);

            return delayed_time;
        }
    };
}