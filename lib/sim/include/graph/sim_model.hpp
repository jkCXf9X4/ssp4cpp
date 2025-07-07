#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "data_buffer.hpp
#include "data_storage.hpp

#include "fmu_handler.hpp"

#include <string>
#include <vector>
#include <functional>

namespace ssp4cpp::sim::graph
{

    class SimModelNode : public ssp4cpp::common::graph::Node
    {
        uint64_t delay = 0;
        uint64_t start_time = 0;
        uint64_t end_time = 0;
        uint64_t delayed_time = 0;

    public:
        common::Logger log = common::Logger("SimModelNode", common::LogLevel::info);

        handler::FmuInfo *fmu;

        utils::DataStorage input_area;
        utils::RingStorage input_area;
        
        vector<function<void()>> inputs;
        vector<function<void()>> outputs;

        SimModelNode() {}

        SimModelNode(std::string name, handler::FmuInfo *fmu)
        {
            this->fmu = fmu;
            this->name = name;
        }

        ~SimModelNode()
        {
            log.ext_trace("[{}] Destroying SimModelNode", __func__);
        }

        friend ostream &operator<<(ostream &os, const SimModelNode &obj)
        {
            os << "SimModelNode { \n"
               << "Name: " << obj.name << endl
               << " }" << endl;

            return os;
        }

        void pre(uint64_t time)
        {
            log.ext_trace("[{}] Init", __func__);
            // fetch all data to enable running the model

        }

        
        void take_step(uint64_t timestep)
        {
            auto step_double = (double)timestep / ssp4cpp::common::time::nanoseconds_per_second;
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
            // store the resulting data from the model

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