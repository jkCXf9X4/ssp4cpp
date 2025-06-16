#pragma once

#include "common_node.hpp"
#include "common_map.hpp"
#include "common_string.hpp"
#include "common_time.hpp"

#include "node_base.hpp"
#include "node_connector.hpp"

#include "fmu_handler.hpp"

#include "fmu.hpp"
#include <fmi4cpp/fmi4cpp.hpp>

#include <string>
#include <vector>

namespace ssp4cpp::sim::graph
{

    class ModelNode : public NodeBase
    {
    public:
        common::Logger log = common::Logger("ModelNode", common::LogLevel::ext_trace);

        string fmu_name;

        map<string, ConnectorNode *> input_connectors;
        map<string, ConnectorNode *> output_connectors;

        uint64_t start_time = 0;
        uint64_t end_time = 0;
        uint64_t delayed_time = 0;
        uint64_t delay = 0;

        handler::FmuInfo *fmu;

        ModelNode() {}

        ModelNode(std::string name, std::string fmu_name, handler::FmuInfo *fmu)
        {
            this->fmu = fmu;
            this->name = name;
            this->fmu_name = fmu_name;
        }

        ~ModelNode()
        {
            log.ext_trace("[{}] Destroying ModelNode", __func__);
        }

        friend ostream &operator<<(ostream &os, const ModelNode &obj)
        {
            os << "Model { \n"
               << "Name: " << obj.name << endl
               << "Fmu: " << obj.fmu_name << endl
               << " }" << endl;

            return os;
        }

        void set_input(uint64_t time)
        {
            log.ext_trace("[{}] Init", __func__);
            for (auto &[_, c] : input_connectors)
            {
                //TODO: get some connection delay...
                c->write_to_model(time);
            }
        }
        
        void get_output(uint64_t time)
        {
            log.ext_trace("[{}] Init", __func__);
            for (auto &[_, c] : output_connectors)
            {
                c->read_from_model(time);
            }
        }
        
        void take_step(uint64_t timestep)
        {
            log.ext_trace("[{}] Init", __func__);
            auto step_double = (double)timestep / ssp4cpp::common::time::nanoseconds_per_second;
            log.trace("[{}] Model {} ", __func__, step_double);
            if (fmu->model->step(step_double) == false)
            {
                log.error("Error! step() returned with status: {}", std::to_string((int)fmu->model->last_status()));
            }
        }
        
        uint64_t invoke(uint64_t timestep)
        {
            log.ext_trace("[{}] Init {}", __func__, this->name.c_str());

            start_time = end_time;
            end_time = start_time + timestep;
            delayed_time = end_time - delay;
            log.trace("[{}] SimNode start_time: {} end_time: {}, delayed_time {}", __func__, start_time, end_time, delayed_time);
            
            set_input(start_time);

            take_step(timestep);

            get_output(delayed_time);

            return delayed_time;
        }
    };
}