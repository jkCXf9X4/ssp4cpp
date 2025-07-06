#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "node_base.hpp"

#include "data_buffer.hpp
#include "data_storage.hpp

#include "fmu_handler.hpp"

#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{

    class SimModelNode : public NodeBase
    {
    public:
        common::Logger log = common::Logger("SimModelNode", common::LogLevel::info);

        string fmu_name;

        handler::FmuInfo *fmu;

        

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

        void retrieve_and_set_input(uint64_t time)
        {
            log.ext_trace("[{}] Init", __func__);

            connectors.write_to_model(time);
        }
        
        void store_output(uint64_t time)
        {
            connectors.read_from_model(time);
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
        
        uint64_t invoke(uint64_t time)
        {
            start_time = end_time;
            end_time = time;
            auto timestep = end_time - start_time;
            delayed_time = end_time - delay;
            
            log.trace("[{}] {} start_time: {} timestep: {} end_time: {}, delayed_time {}", 
                __func__, this->name.c_str(), start_time, timestep, end_time, delayed_time);
            
            retrieve_and_set_input(start_time);

            take_step(timestep);
            // this should return the new endtime if we have early return

            store_output(delayed_time);

            return delayed_time;
        }
    };
}