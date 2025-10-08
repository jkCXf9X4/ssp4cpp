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
        common::Logger log = common::Logger("ssp4sim.model.FmuModel", common::LogLevel::info);

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

        void init()
        {
            log.trace("[{}] FmuModel init {}", __func__, name);

            double start_time = utils::Config::get<double>("simulation.start_time");
            double end_time = utils::Config::get<double>("simulation.stop_time") + 10;
            double tolerance = utils::Config::get<double>("simulation.tolerance");

            log.debug("[{}] setup_experiment: {} ", __func__, name);
            if (!fmu->model->setup_experiment(common::time::s_to_ns(start_time), common::time::s_to_ns(end_time), tolerance))
                log.error("[{}] setup_experiment failed ", __func__);

            log.debug("[{}] enter_initialization_mode: {} ", __func__, name);
            if (!fmu->model->enter_initialization_mode())
            {
                log.error("[{}] enter_initialization_mode failed ", __func__);
                throw std::runtime_error(std::format("[{}] enter_initialization_mode failed for {}", __func__, name));
            }

            log.trace("[{}] Set start parameter values", __func__);
            ConnectorInfo::set_start_values(this->parameters);

            log.debug("[{}] exit_initialization_mode: {} ", __func__, name);
            if (!fmu->model->exit_initialization_mode())
            {
                log.error("[{}] exit_initialization_mode failed ", __func__);
                throw std::runtime_error(std::format("[{}] exit_initialization_mode failed for {}", __func__, name));
            }

            log.ext_trace("[{}] Set input area", __func__);
            ConnectorInfo::set_initial_input_area(this->input_area.get(), this->inputs);

            log.ext_trace("[{}] Invoke at timestep 0", __func__);
            invoke(StepData(0, 0, 0));

            log.ext_trace("[{}] FmuModel init completed", __func__);
        }

        // hot path
        inline void pre(uint64_t model_start_time, uint64_t valid_input_time)
        {
            IF_LOG({
                log.trace("[{}] Init. model_start_time {}, valid_input_time {}", __func__, model_start_time, valid_input_time);
            });

            auto target_area = input_area->push(model_start_time);

            ConnectionInfo::retrieve_model_inputs(connections, target_area, valid_input_time);

            input_area->flag_new_data(target_area);

            ConnectorInfo::write_data_to_model(inputs, input_area.get(), target_area);

            if (forward_derivatives)
            {
                auto model_timer = common::time::Timer();
                ConnectorInfo::apply_input_derivatives(inputs, target_area);
                this->walltime_ns += model_timer.stop();
            }

            IF_LOG({
                log.ext_trace("[{}] Input area after pre: {}", __func__, input_area->data->export_area(target_area));
            });
        }

        // hot path
        inline void post(uint64_t time)
        {
            IF_LOG({
                log.trace("[{}] Store results, timestamp: {}", __func__, time);
            });

            auto area = output_area->push(time);

            ConnectorInfo::read_values_from_model(outputs, output_area.get(), area);

            if (forward_derivatives && _end_time != 0)
            {
                auto model_timer = common::time::Timer();
                ConnectorInfo::fetch_output_derivatives(outputs, area);
                this->walltime_ns += model_timer.stop();
            }
            output_area->flag_new_data(area);

            IF_LOG({
                log.ext_trace("[{}] Output area after post: {}", __func__, output_area->data->export_area(area));
            });
        }

        inline uint64_t step(StepData step_data)
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

            auto model_timer = common::time::Timer();
            IF_LOG({
                log.debug("[{}] Step until {}", __func__, _end_time);
            });
            _end_time = fmu->model->step_until(_end_time);
            this->walltime_ns += model_timer.stop();

            auto delayed_time = _end_time - delay;
            post(delayed_time);
            IF_LOG({
                log.ext_trace("[{}] Completed, delayed_time:", __func__, delayed_time);
            });

            return delayed_time;
        }

        // Not optimized at all... need to only propagate the direct feedthru signals
        // This is now allowed...
        // there need to be a step between the set and get....
        inline uint64_t direct_feedthrough(uint64_t start)
        {
            auto target_area = input_area->get_or_push(start);

            IF_LOG({
                log.info("[{}] Propagating at start_time {}, input_area {} timestamp {}", __func__, start,target_area, input_area->data->timestamps[target_area]);
            });

            ConnectionInfo::retrieve_model_inputs(connections, target_area, start);

            ConnectorInfo::write_data_to_model(inputs, input_area.get(), target_area);

            // _end_time = fmu->model->step();

            auto area = output_area->get_or_push(start);

            IF_LOG({
                log.info("[{}] Propagating at start_time {}, output area {} timestamp {}", __func__, start, area, output_area->data->timestamps[area]);
            });

            ConnectorInfo::read_values_from_model(outputs, output_area.get(), area);
            return start;
        }

        // hot path
        uint64_t invoke(StepData step_data, const bool only_feedthrough = false) override final
        {
            if (only_feedthrough)
            {
                // The direct feedthru loop will be stored in start +1ns
                // valid_input_time need to be increased by one to take this into account
                // work but is not allowed according to standard
                // causes a hard time for the solvers leading to massive walltime increase 10x
                return this->direct_feedthrough(step_data.start_time + 1);
            }
            else
            {
                step_data.valid_input_time += 1;
                return step(step_data);
            }
        }
    };
}
